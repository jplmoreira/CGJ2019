#include "bloom.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

void bloom::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void bloom::window_size_callback(GLFWwindow* win, int winx, int winy) {
	SCR_WIDTH = winx;
	SCR_HEIGHT = winy;
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void bloom::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {}

void bloom::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void bloom::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

void bloom::setup(int winx, int winy) {
	SCR_WIDTH = winx;
	SCR_HEIGHT = winy;
	setup_shaders(); 
	create_fbos();
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 0.0f, 5.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(0.0f, 1.0f, 0.0f));
	
	engine::manager::mesh_manager::get_instance()->elements["cube"] =
		std::make_shared<engine::geometry::mesh>("res/models/cube.obj");
	engine::manager::mesh_manager::get_instance()->elements["quad"] = 
		std::make_shared<engine::geometry::mesh>("res/models/quad.obj");

	//main scene
	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>(); //criar main scene
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"]; //passamos main shader para o root obj
	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>(); //criamos um object
	obj->m = engine::manager::mesh_manager::get_instance()->elements["cube"]; //passamos-lhe a mesh do cubo
	obj->transform = engine::math::mat_fact::scale(0.4f, 0.4f, 0.4f); //transformamos o cubo
	std::shared_ptr<engine::texture> tex = std::make_shared<engine::texture>("res/models/cube_texture.png"); //criamos a textura para o cubo
	obj->textures.push_back(tex); //passamos a textura para o cubo
	main_scene->root_obj->add_node(obj); //adicionamos o cubo completo ao root node
	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene; //guardamos a cena no scene manager

	//blur scene - semelhante, mas em vez do cubo criamos o quad para projectar o resultado e a textura é o resultado dos color buffers
	std::shared_ptr<engine::scene> blur_scene = std::make_shared<engine::scene>();
	blur_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["blur"];  
	std::unique_ptr<engine::geometry::object> quad_obj = std::make_unique<engine::geometry::object>();
	quad_obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	std::shared_ptr<engine::texture> image = std::make_shared<engine::texture>(color_buffers[1]);
	quad_obj->textures.push_back(image); //passamos a textura para o 2dsampler image
	blur_scene->root_obj->add_node(quad_obj);
	engine::manager::scene_manager::get_instance()->elements["blur"] = blur_scene;

	//bloom scene
	std::shared_ptr<engine::scene> bloom_scene = std::make_shared<engine::scene>();
	bloom_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["bloom"];
	quad_obj = std::make_unique<engine::geometry::object>();
	quad_obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	std::shared_ptr<engine::texture> scene = std::make_shared<engine::texture>(color_buffers[0]);
	std::shared_ptr<engine::texture> bloom_blur = std::make_shared<engine::texture>(pingpong_color_buffers[0]);
	quad_obj->textures.push_back(scene);
	quad_obj->textures.push_back(bloom_blur);
	bloom_scene->root_obj->add_node(quad_obj);
	engine::manager::scene_manager::get_instance()->elements["bloom"] = bloom_scene;
}

void bloom::display(float elapsed_sec) {
	//main
	glBindFramebuffer(GL_FRAMEBUFFER, bloom_fbo);       //bind do fbo inicial
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear dos buffers
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec); //atualizar a camera
	engine::manager::scene_manager::get_instance()->elements["main"]->draw();  //draw da main scene
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind framebuffer (bind ao default)

	//blur
	bool horizontal = true; //para irmos passando para o fbo correspondente
	bool first_iteration = true; //começamos na 1a iteraçao por adicionar o color buffer que contem os bright elements e dps desligamos para o pingpong
	const int amount = 100; //nr de vezes que fazemos blur
	std::shared_ptr<engine::shader> blur_shdr = engine::manager::shader_manager::get_instance()->elements["blur"]; //criamos shader de blur
	for (int i = 0; i < amount; i++) { //fazemos bind do framebuffer segundo a flag horizontal e fazemos blur, numero de vezes amount
		glBindFramebuffer(GL_FRAMEBUFFER, pingpong_fbos[horizontal]);
		blur_shdr->enable();
		glUniform1i(blur_shdr->uniforms["horizontal"], horizontal); //passamos o valor da flag para o shader para ele saber que blur fazer
		blur_shdr->disable();
		if(first_iteration)  //se for a primeira iteraçao
			engine::manager::scene_manager::get_instance()->elements["blur"]->    //passamos o color buffer da brightness para o color buffer do active framebuffer
			root_obj->children[0]->textures[0]->id = color_buffers[1];
		else
			engine::manager::scene_manager::get_instance()->elements["blur"]->    //caso contrario passamos o color buffer do framebuffer oposto 
			root_obj->children[0]->textures[0]->id = pingpong_color_buffers[!horizontal];                         //para o color buffer do active framebuffer
		engine::manager::scene_manager::get_instance()->elements["blur"]->draw(); //e fazemos draw na cena
		horizontal = !horizontal;  //trocamos a flag para fazer o oposto
		if (first_iteration)
			first_iteration = false; //desligamos a primeira iteraçao
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind do framebuffer (bind ao default)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear dos buffers

	//bloom
	engine::manager::scene_manager::get_instance()->elements["bloom"]->   //passamos a textura do render normal
		root_obj->children[0]->textures[0]->id = color_buffers[0];
	engine::manager::scene_manager::get_instance()->elements["bloom"]->   //e passamos a textura blurred
		root_obj->children[0]->textures[1]->id = pingpong_color_buffers[!horizontal];
	engine::manager::scene_manager::get_instance()->elements["bloom"]->draw();  //e fazemos draw do blend
}

void bloom::setup_shaders() {
	std::shared_ptr<engine::shader> main = std::make_shared<engine::shader>();            
	main->compile("res/shaders/bright_vert.glsl", "res/shaders/bright_frag.glsl");        
	main->uniforms["ModelMatrix"] = glGetUniformLocation(main->get_id(), "ModelMatrix");  
	GLint ubo_id = glGetUniformBlockIndex(main->get_id(), "SharedMatrices");              
	main->blocks["SharedMatrices"] = 0;                                                   
	glUniformBlockBinding(main->get_id(), ubo_id, main->blocks["SharedMatrices"]);        
	main->cleanup();                                                                      
	main->enable();                                                                       
	glUniform1i(glGetUniformLocation(main->get_id(), "tex"), 0); //uniform texture initialization
	main->disable();                                                                      
	engine::manager::shader_manager::get_instance()->elements["main"] = main;             


	std::shared_ptr<engine::shader> blur = std::make_shared<engine::shader>();             
	blur->compile("res/shaders/blur_vert.glsl", "res/shaders/blur_frag.glsl");            
	blur->uniforms["horizontal"] = glGetUniformLocation(blur->get_id(), "horizontal");    
	blur->cleanup();                                                                      
	blur->enable();                                                                       
	glUniform1i(glGetUniformLocation(blur->get_id(), "image"), 0); //uniform texture initialization
	blur->disable();                                                                      
	engine::manager::shader_manager::get_instance()->elements["blur"] = blur;             


	std::shared_ptr<engine::shader> bloom = std::make_shared<engine::shader>();           
	bloom->compile("res/shaders/bloom_vert.glsl", "res/shaders/bloom_frag.glsl");         
	bloom->cleanup();                                                                     
	bloom->enable();                                                                      
	glUniform1i(glGetUniformLocation(bloom->get_id(), "scene"), 0);                       //uniform texture initialization
	glUniform1i(glGetUniformLocation(bloom->get_id(), "bloom_blur"), 1);                  //uniform texture initialization
	bloom->disable();                                                                     
	engine::manager::shader_manager::get_instance()->elements["bloom"] = bloom;           
}

void bloom::create_fbos() {
	//create bloom fbo
	glGenFramebuffers(1, &bloom_fbo);                  //criamos o fbo inicial
	glBindFramebuffer(GL_FRAMEBUFFER, bloom_fbo);      //fazemos bind
	glGenTextures(2, color_buffers);				   //geramos duas texturas para os dois color buffers, 
													   //porque we specify a color attachment when linking a texture as a framebuffer's colorbuffer

	for (int i = 0; i < 2; i++) {  //como temos 2 fragment shader outputs, precisamos de fazer attach dos dois colorbuffers ao currently bound framebuffer
		glBindTexture(GL_TEXTURE_2D, color_buffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, color_buffers[i], 0); //we specify a color attachment when linking 
																										      //a texture as a framebuffer's colorbuffer
	}
	
	//create depth rbo
	GLuint rbo_depth;
	glGenRenderbuffers(1, &rbo_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 }; //we have to tell opengl we're rendering to multiple colorbuffers
	glDrawBuffers(2, attachments);										    //otherwise opengl only renders to the first color attachment
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//create pingpongs
	glGenFramebuffers(2, pingpong_fbos);  //criamos dois framebuffers
	glGenTextures(2, pingpong_color_buffers); //cada um com 1 color buffer texture
	
	for (int i = 0; i < 2; i++) {   //tal como anterior, fazemos bind de cada texture, neste caso 1 para cada framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, pingpong_fbos[i]); //bind do framebuffer feito no ciclo para ter 1 só color buffer atribuido no proprio ciclo
		glBindTexture(GL_TEXTURE_2D, pingpong_color_buffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpong_color_buffers[i], 0);
		
		//check if framebuffers are complete dentro do ciclo porque é bound dentro do ciclo
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete." << std::endl;
	}
	
}