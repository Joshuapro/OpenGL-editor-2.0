// This example is heavily based on the tutorial at https://open.gl

// OpenGL Helpers to reduce the clutter
#include "Helpers.h"
#include "ebo.h"
#include "cube.h"
#include "plane.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <math.h> 

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
#else
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
#endif

// OpenGL Mathematics Library
#include <glm/glm.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <fstream>
#include <sstream>
#include <iostream>
// Timer
#include <chrono>
#include <iostream>
#include <exception>




int shading_mode = 2;
int globalPickedId = -1;
std::vector<Cube> cubes;
std::vector<Bunny> bunnies;
std::vector<Bumpy> bumpies;
std::vector<Plane> plane;
float timee = 0;

int total_object = 151;
// VertexBufferObject wrapper
VertexBufferObject VBO;
EBO ebo;
// Contains the vertex positions
//Eigen::MatrixXf V(2,3);
const unsigned int width = 640;
const unsigned int height = 480;
const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
std::vector<glm::vec3> V;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 proj = glm::mat4(1.0f);

glm::vec3 platform = glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 objectColor(0.73f);
glm::vec3 target(0.0f, 0.0f,0.0f);
glm::vec3 init = glm::vec3(0.0f,0.0f,3.0f);
glm::mat4 projection;
bool ortho = false;
glm::vec3 lightPos(-3.0f, 3.0f, 0.0f);




float hori = 0;
float verti = 0;
float r = 1;
int display_mode = 0;
Program program;
Program programShading;
// Program cubeBoxProgram;

int redShade = 0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

 void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
 {
     // Get the position of the mouse in the window
     double xpos, ypos;
     glfwGetCursorPos(window, &xpos, &ypos);
     // Get the size of the window
     int width, height;
     glfwGetWindowSize(window, &width, &height);
     // Convert screen position to world coordinates
     double xworld = ((xpos/double(width))*2)-1;
     double yworld = (((height-1-ypos)/double(height))*2)-1; // NOTE: y axis is flipped in glfw

	
	int prev = globalPickedId;
	

	glReadPixels(xpos, height-1-ypos,1,1,GL_STENCIL_INDEX,GL_INT, &globalPickedId);
	
	std::cout <<globalPickedId << std::endl;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		if (globalPickedId != prev && globalPickedId != 0){
			// std::cout << globalPickedId << std::endl;
			for (int i = 0; i < cubes.size(); i++) {
				if (cubes[i].uid == globalPickedId) {
					cubes[i].color = glm::vec3(0, 1, 0);
				}
				if (cubes[i].uid == prev) {
					cubes[i].color = glm::vec3(0.73f);
				}
			}
			for (int i = 0; i < bunnies.size(); i++) {
				if (bunnies[i].uid == globalPickedId) {
					bunnies[i].color = glm::vec3(0, 1, 0);
				}
				if (bunnies[i].uid == prev) {
					bunnies[i].color = glm::vec3(0.73f);
				}
			}
			for (int i = 0; i < bumpies.size(); i++) {
				if (bumpies[i].uid == globalPickedId) {
					bumpies[i].color = glm::vec3(0, 1, 0);
				}
				if (bumpies[i].uid == prev) {
					bumpies[i].color = glm::vec3(0.73f);
				}
			}
		}else if (globalPickedId == 150){
			for (int i = 0; i < cubes.size(); i++) {
				cubes[i].color = glm::vec3(0.73f);
			}
			for (int i = 0; i < bunnies.size(); i++) {
				bunnies[i].color = glm::vec3(0.73f);
			}
			for (int i = 0; i < bumpies.size(); i++) {
				bumpies[i].color = glm::vec3(0.73f);
			}
		}
	}

	
	


 }

 void scaleObject(int dir) {
	 float at = 0;
	 if (dir == 0) {//up
		 at += 0.1;

	 }
	 else if (dir == 1) {//up
		 at -= 0.1;

	 }
	 if (globalPickedId < 0) return;
	 for (int i = 0; i < cubes.size(); i++) {
		 if (cubes[i].uid == globalPickedId) {
			 cubes[i].objsize += at;
			 return;
		 }
	 }
	 for (int i = 0; i < bunnies.size(); i++) {
		 if (bunnies[i].uid == globalPickedId) {
			 bunnies[i].objsize += at;
			 return;
		 }
	 }
	 for (int i = 0; i < bumpies.size(); i++) {
		 if (bumpies[i].uid == globalPickedId) {
			 bumpies[i].objsize += at;
		 }
	 }



 }
void rotateObject(int dir) {
	float at = 0;
	float dy = 0;
	if (dir == 0) {//up
		at += 0.1;
	}
	if (dir == 1) {//up
		at -= 0.1;
	}
	if (dir == 2){
		dy += 0.1;
	}

	if (dir == 3){
		dy -= 0.1;
	}
	if (globalPickedId < 0) return;
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i].uid == globalPickedId) {
			cubes[i].angleY += at;
			cubes[i].angleX += dy;
			return;
		}
	}
	for (int i = 0; i < bunnies.size(); i++) {
		if (bunnies[i].uid == globalPickedId) {
			bunnies[i].angleY += at;
			bunnies[i].angleX += dy;
			return;
		}
	}
	for (int i = 0; i < bumpies.size(); i++) {
		if (bumpies[i].uid == globalPickedId) {
			bumpies[i].angleY += at;
			bumpies[i].angleX += dy;
		}
	} 
	
	

}
void deleteObject() {
	if (globalPickedId < 0) return;
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i].uid == globalPickedId) {
			cubes[i].uid = -1;
			return;
		}
	}
	for (int i = 0; i < bunnies.size(); i++) {
		if (bunnies[i].uid == globalPickedId) {
			bunnies[i].uid = -1;
			return;
		}
	}
	for (int i = 0; i < bumpies.size(); i++) {
		if (bumpies[i].uid == globalPickedId) {
			bumpies[i].uid = -1;
		}
	}
}

void moveObject(int dir) {
	if (globalPickedId < 0) return;
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i].uid == globalPickedId) {
			if (dir == 0) {//up
				cubes[i].modelpos.z += 0.1;
			}
			else if (dir == 1) {//up
				cubes[i].modelpos.z -= 0.1;
			}
			else if (dir == 2) {//up
				cubes[i].modelpos.x -= 0.1;
			}
			else if (dir == 3) {//up
				cubes[i].modelpos.x += 0.1;
			}
			else if (dir == 5) {//up
				cubes[i].modelpos.y -= 0.1;
			}
			else if (dir == 6) {//up
				cubes[i].modelpos.y += 0.1;
			}
			return;
		}
	}
	for (int i = 0; i < bunnies.size(); i++) {
		if(bunnies[i].uid == globalPickedId){
			if (dir == 0) {
				bunnies[i].modelpos.z += 0.1;
			}
			else if (dir == 1) {
				bunnies[i].modelpos.z -= 0.1;
			}
			else if (dir == 2) {
				bunnies[i].modelpos.x -= 0.1;
			}
			else if (dir == 3) {
				bunnies[i].modelpos.x += 0.1;
			}
			else if (dir == 5) {
				bunnies[i].modelpos.y -= 0.1;
			}
			else if (dir == 6) {
				bunnies[i].modelpos.y += 0.1;
			}
			return;
		}
	}
	for (int i = 0; i < bumpies.size(); i++) {
		if (bumpies[i].uid == globalPickedId) {
			if (dir == 0) {
				bumpies[i].modelpos.z += 0.1;
			}
			else if (dir == 1) {
				bumpies[i].modelpos.z -= 0.1;
			}
			else if (dir == 2) {
				bumpies[i].modelpos.x -= 0.1;
			}
			else if (dir == 3) {
				bumpies[i].modelpos.x += 0.1;
			}
			else if (dir == 5) {
				bumpies[i].modelpos.y -= 0.1;
			}
			else if (dir == 6) {
				bumpies[i].modelpos.y += 0.1;
			}
			return;
		}
	}
	
	

}

void change(int num){
	if (globalPickedId < 0) return;
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i].uid == globalPickedId) {
			cubes[i].mode = num;
			return;
		}
	}
	for (int i = 0; i < bunnies.size(); i++) {
		if (bunnies[i].uid == globalPickedId) {
			bunnies[i].mode = num;
			return;
		}
	}
	for (int i = 0; i < bumpies.size(); i++) {
		if (bumpies[i].uid == globalPickedId) {
			bumpies[i].mode = num;

			return;
		}
	}
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Update the position of the first vertex if the keys 1,2, or 3 are pressed
    switch (key)
    {
        case GLFW_KEY_1:
            if (action == GLFW_PRESS){
                Cube hi;
				hi.uid = total_object++;
				hi.shading_mode = shading_mode;
                cubes.push_back(hi);
            }
            break;
        case GLFW_KEY_2:
            if (action == GLFW_PRESS){
                Bunny bun("../data/bunny.off");
				bun.shading_mode = shading_mode;
				bun.uid = total_object++;
				bun.calcNormal();
				bun.pushVec();
                bunnies.push_back(bun);
            }
            break;
        case GLFW_KEY_3:
            if (action == GLFW_PRESS){
                Bumpy bum("../data/bumpy_cube.off");
				bum.shading_mode = shading_mode;
				bum.uid = total_object++;
				bum.calcNormal();
				bum.pushVec();
                bumpies.push_back(bum);
            }
			break;
        case GLFW_KEY_T:
            if (action == GLFW_PRESS){
				deleteObject();
            }
			break;
		case GLFW_KEY_P:
			if (action == GLFW_PRESS) {
				change(2);
			}
			break;
		case GLFW_KEY_F:
			
			if (action == GLFW_PRESS) {
				change(0);
			}
			break;
		case GLFW_KEY_W:
			moveObject(0);
			break;
		case GLFW_KEY_S:
			moveObject(1);
			break;
		case GLFW_KEY_A:
			moveObject(2);
			break;
		case GLFW_KEY_D:
			moveObject(3);
			break;
		case GLFW_KEY_U:
			moveObject(5);
			break;
		case GLFW_KEY_Y:
			moveObject(6);
			break;
		case GLFW_KEY_E:
			rotateObject(0);
			break;
		case GLFW_KEY_R:
			rotateObject(1);
			break;
		case GLFW_KEY_I:
			rotateObject(2);
			break;
		case GLFW_KEY_O:
			rotateObject(3);
			break;
		case GLFW_KEY_G:
			scaleObject(0);
			break;
		case GLFW_KEY_H:
			scaleObject(1);
			break;
		case GLFW_KEY_UP:
			if (action == GLFW_PRESS){
				ortho = !ortho;
			}
			break;
		case GLFW_KEY_Z:
			init.x += 0.1;
			break;
		case GLFW_KEY_X:
			init.x -= 0.1;
			break;
		case GLFW_KEY_C:
			init.y += 0.1;
			break;
		case GLFW_KEY_V:
			init.y -= 0.1;
			break;
		case GLFW_KEY_4:
			platform.x += 0.1;
			break;
		case GLFW_KEY_5:
			platform.x -= 0.1;
			break;
		case GLFW_KEY_6:
			platform.y -= 0.1;
			break;
		case GLFW_KEY_7:
			platform.y += 0.1;
			break;
		case GLFW_KEY_8:
			if (action == GLFW_PRESS){
				timee += 0.2;
				lightPos.x += sin(timee) * 0.5;
				lightPos.z += cos(timee) * 0.5;
			}
			break;
		case GLFW_KEY_B:
			if (action == GLFW_PRESS){
				if (redShade == 0) redShade = 1;
				else redShade = 0;
			}
			break;
        default:
            break;
    }

    // Upload the change to the GPU
    VBO.update(V);
}

// loads a cubemap texture from 6 individual texture faces
unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data){
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}else{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}


// Program getProgram() {
	 
// 	const GLchar* fragment_shader =
// 		"#version 330 core\n"
// 		"out vec4 outColor;\n"
// 		"in vec3 Normal;\n"
// 		"in vec3 Position;\n"

// 		"uniform vec3 cameraPos;\n"
// 		"uniform samplerCube skybox;\n"

// 		"void main()\n"
// 		"{    \n"
// 		"    vec3 I = normalize(Position - cameraPos);\n"
// 		"    vec3 R = reflect(I, normalize(Normal));\n"
// 		"    outColor = vec4(texture(skybox, R).rgb, 1.0);\n"
// 		"}\n";
// 	const GLchar* vertex_shader =
// 		"#version 330 core\n"
// 		"layout (location = 0) in vec3 aPos;\n"
// 		"layout (location = 1) in vec3 aNormal;\n"

// 		"out vec3 Normal;\n"
// 		"out vec3 Position;\n"
// 		"uniform mat4 model;\n"
// 		"uniform mat4 view;\n"
// 		"uniform mat4 projection;\n"

// 		"void main()\n"
// 		"{\n"
// 		"    Normal = mat3(transpose(inverse(model))) * aNormal;\n"
// 		"    Position = vec3(model * vec4(aPos, 1.0));\n"
// 		"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
// 		"}\n";

// 	// Compile the two shaders and upload the binary to the GPU
// 	// Note that we have to explicitly specify that the output "slot" called outColor
// 	// is the one that we want in the fragment buffer (and thus on screen)
// 	cubeBoxProgram.init(vertex_shader, fragment_shader, "outColor");
// 	cubeBoxProgram.bind();
// 	return cubeBoxProgram;
// }
Program getMainProgram() {

	const GLchar* fragment_shader =
		"#version 330 core\n"
		"out vec4 outColor;\n"

		"in VS_OUT {\n"
		"    vec3 FragPos;\n"
		"    vec3 Normal;\n"
		"    vec4 FragPosLightSpace;\n"
		"} fs_in;\n"

		"uniform sampler2D shadowMap;\n"
		"uniform vec3 objectColor;\n"
		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;\n"
		"uniform int mode;\n"
		"uniform int redon;\n"

		"in vec3 envNormal;\n"
		"in vec3 envPosition;\n"
		"uniform vec3 cameraPos;\n"
		"uniform samplerCube skybox;\n"

		"float ShadowCalculation(vec4 fragPosLightSpace)\n"
		"{\n"

		"    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;\n"

		"    projCoords = projCoords * 0.5 + 0.5;\n"
		"    float closestDepth = texture(shadowMap, projCoords.xy).r; \n"

		"    float currentDepth = projCoords.z;\n"
		"	vec3 normal = normalize(fs_in.Normal);"
    	"	vec3 lightDir = normalize(lightPos - fs_in.FragPos);"
		// "	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);"
		"	float bias = 0.005;"
		"    float shadow = 0.0;\n"
		"    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);\n"
		"    for(int x = -1; x <= 1; ++x)\n"
		"    {\n"
		"        for(int y = -1; y <= 1; ++y)\n"
		"        {\n"
		"            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; \n"
		"            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        \n"
		"        }    \n"
		"    }\n"
		"    shadow /= 9.0;\n"

		"    if(projCoords.z > 1.0)\n"
		"        shadow = 0.0;\n"

		"    return shadow;\n"
		"	return shadow;"
		
		"}\n"

		"void main()\n"
		"{         \n"
		"    vec3 color = objectColor;\n"
		"    vec3 normal = normalize(fs_in.Normal);\n"
		"    vec3 lightColor = vec3(1);\n"

		"    vec3 ambient = 0.3 * color;\n"

		"    vec3 lightDir = normalize(lightPos - fs_in.FragPos);\n"
		"    float diff = max(dot(lightDir, normal), 0.0);\n"
		"    vec3 diffuse = diff * lightColor;\n"

		"    vec3 viewDir = normalize(viewPos - fs_in.FragPos);\n"
		"    vec3 reflectDir = reflect(-lightDir, normal);\n"
		"    float spec = 5.0;\n"
		"    vec3 halfwayDir = normalize(lightDir + viewDir);\n"
		"    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);\n"
		"    vec3 specular = spec * lightColor;  \n"

		"    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);  \n"
		"    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    \n"


		"	if(mode==0){\n"
		//reflective
		// "		float ratio = 0.658;"
		// "		vec3 I = normalize(envPosition - cameraPos);"
		// "		vec3 R = refract(I, normalize(envNormal), ratio);"
		"		vec3 I = normalize(envPosition - cameraPos);\n"
		"		vec3 R = reflect(I, normalize(envNormal));\n"
		"		outColor = vec4(texture(skybox, R+lighting).rgb, 1.0);\n"
		"	}else if(mode==1){\n"
		//plane
		"		outColor = vec4((1.0 - shadow)*objectColor, 1.0);\n"
		"		if((shadow != 0) && (redon == 1)){outColor = vec4(1.0,0.0,0.0,1.0);}"
		"	}else if(mode==2){\n"
		//phong
		"		outColor = vec4((1.0 - shadow)*lighting, 1.0);\n"
		"		if((shadow != 0) && (redon == 1)){outColor = vec4(1.0,0.0,0.0,1.0);}"
		"	}\n"

		"}\n";
	const GLchar* vertex_shader =
		"#version 330 core\n"
		"in vec3 aPos;\n"
		"in vec3 aNormal;\n"

		"out vec3 envNormal;\n"
		"out vec3 envPosition;\n"

		"out VS_OUT {\n"
		"    vec3 FragPos;\n"
		"    vec3 Normal;\n"
		"    vec4 FragPosLightSpace;\n"
		"} vs_out;\n"

		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"uniform mat4 lightSpaceMatrix;\n"
		"uniform int display_mode;\n"
		"void main()\n"
		"{\n"

		"	envNormal = mat3(transpose(inverse(model))) * aNormal;\n"
		"    envPosition = vec3(model * vec4(aPos, 1.0));\n"
		"    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));\n"
		"    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;\n"
		"    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);\n"

		"	if(display_mode == 1){\n"
		"		gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);\n"
		"	}else{\n"
		"		gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"	}\n"
		"}\n";

	// Compile the two shaders and upload the binary to the GPU
	// Note that we have to explicitly specify that the output "slot" called outColor
	// is the one that we want in the fragment buffer (and thus on screen)
	//program.init(vShaderCode, fShaderCode, "outColor");
	check_gl_error();
	program.bind();

	
	program.init(vertex_shader, fragment_shader, "outColor");
	program.bind();
	program.bindVertexAttribArray("aPos", VBO);
	program.bindVertexAttribArray("aNormal", VBO);
	return program;
}
int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Activate supersampling
    glfwWindowHint(GLFW_SAMPLES, 8);

    // Ensure that we get at least a 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // On apple we have to load a core profile with forward compatibility
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a windowed mode window and its OpenGL context
	// glfwGetPrimarymonitor()
//	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	window = glfwCreateWindow(width, height, "Hello World", glfwGetPrimaryMonitor(), NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	
    // Make the window's context current
    glfwMakeContextCurrent(window);

    #ifndef __APPLE__
      glewExperimental = true;
      GLenum err = glewInit();
      if(GLEW_OK != err)
      {
        /* Problem: glewInit failed, something is seriously wrong. */
       fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      }
      glGetError(); // pull and savely ignonre unhandled errors like GL_INVALID_ENUM
      fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    #endif

    int major, minor, rev;
    major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    printf("OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
    printf("Supported OpenGL is %s\n", (const char*)glGetString(GL_VERSION));
    printf("Supported GLSL is %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Initialize the VAO
    // A Vertex Array Object (or VAO) is an object that describes how the vertex
    // attributes are stored in a Vertex Buffer Object (or VBO). This means that
    // the VAO is not the actual object storing the vertex data,
    // but the descriptor of the vertex data.
    VertexArrayObject VAO;
    VAO.init();
    VAO.bind();

   
    ebo.init();
    ebo.bind();

    // Initialize the VBO with the vertices data
    // A VBO is a data container that lives in the GPU memory
    VBO.init();

    V.resize(1);
    VBO.update(V);

	
	getMainProgram();

	check_gl_error();
	const GLchar* fragment_shader =
		"#version 330 core\n"
		"out vec4 outColor;\n"
		"in vec3 TexCoords; \n"

		"uniform samplerCube skybox; \n"

		"void main()\n"
		"{\n"
		"outColor = texture(skybox, TexCoords); \n"
		"} \n";
	const GLchar* vertex_shader =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"

		"out vec3 TexCoords;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"

		"void main()\n"
		"{\n"
		"TexCoords = aPos;\n"
		"vec4 pos = projection * view * vec4(aPos, 1.0);\n"
		"gl_Position = pos.xyww;\n"
		"}\n";
	 
    // Compile the two shaders and upload the binary to the GPU
    // Note that we have to explicitly specify that the output "slot" called outColor
    // is the one that we want in the fragment buffer (and thus on screen)
	programShading.init(vertex_shader, fragment_shader,"outColor");
	programShading.bind();

	// getProgram();
	check_gl_error();
    // The vertex shader wants the position of the vertices as an input.
    // The following line connects the VBO we defined above with the position "slot"
    // in the vertex shader
	//programShading.bindVertexAttribArray("aPos",VBO);
	check_gl_error();
    // Save the current time --- it will be used to dynamically change the triangle color
    auto t_start = std::chrono::high_resolution_clock::now();

    // Register the keyboard callback
    glfwSetKeyCallback(window, key_callback);

    // Register the mouse callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Update viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);


	std::vector<std::string> faces
	{
		"../data/night_posx.png",
		"../data/night_negx.png",
		"../data/night_posy.png",
		"../data/night_negy.png",
		"../data/night_posz.png",
		"../data/night_negz.png",
		
		
	};
	unsigned int cubemapTexture = loadCubemap(faces);
	float cubeVertices[] = {
		// positions          // normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	float skyboxVertices[] = {
		// positions          
		-10.0f,  10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,
		 10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		 10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		-10.0f,  10.0f, -10.0f,
		 10.0f,  10.0f, -10.0f,
		 10.0f,  10.0f,  10.0f,
		 10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		 10.0f, -10.0f, -10.0f,
		 10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		 10.0f, -10.0f,  10.0f
	};

	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	Plane p;
	plane.push_back(p);
	Cube skybox;
	// configure depth map FBO
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	check_gl_error();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Bind your VAO (not necessary if you have only one)
        VAO.bind();
        ebo.bind();
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
        // Set the uniform value depending on the time difference
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();


    

        // Clear the framebuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);


        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 proj = glm::mat4(1.0f);


		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
		static float n = 0;
		n += 0.5;

		
		glm::vec3 viewPos(0.0f, -1.0f, 0.0f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

		 
		view = glm::lookAt(init,glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0,1.0,0.0));
		if (ortho){
			projection = glm::ortho(-2.0f, 2.0f, -1.5f ,1.5f ,0.1f, 5.0f);
		}
		else{
			projection = glm::perspective(glm::radians(65.0f), (float) width / height, 0.01f, 1000.0f); 
		}


		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// depth of scene to texture 
	
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 7.5f;
	
		lightProjection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;

		program.bind();
		
		glUniform1i(program.uniform("display_mode"), 1);
		
		glUniformMatrix4fv(program.uniform("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);


		for (int i = 0; i < cubes.size(); i++) {
			if (cubes[i].uid == -1) {
				continue;
			}
			if (cubes[i].shading_mode == 0) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(cubes[i].color));
			glStencilFunc(GL_ALWAYS, cubes[i].uid, -1);
			VBO.update(cubes[i].posvec);
			ebo.update(cubes[i].ind);
			auto model = glm::translate(glm::mat4(1.0f), cubes[i].modelpos);
			model = glm::rotate(model, cubes[i].angleY, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, cubes[i].angleX, glm::vec3(1.0f, 0.0f, 0.0f));
			float objsize = cubes[i].objsize;
			model = glm::scale(model, glm::vec3(objsize, objsize, objsize));
			glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}


		for (int i = 0; i < bunnies.size(); i++) {
			if (bunnies[i].uid == -1) {
				continue;
			}

			if (bunnies[i].shading_mode == 0) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(bunnies[i].color));
			glStencilFunc(GL_ALWAYS, bunnies[i].uid, -1);


			VBO.update(bunnies[i].posvec);
			ebo.update(bunnies[i].indvec);
			auto model = glm::translate(glm::mat4(1.0f), bunnies[i].modelpos);
			model = glm::rotate(model, bunnies[i].angleY, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, bunnies[i].angleX, glm::vec3(1.0f, 0.0f, 0.0f));
			float objsize = bunnies[i].objsize;
			model = glm::scale(model, glm::vec3(objsize, objsize, objsize));
			glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, (0));

		}

		for (int i = 0; i < bumpies.size(); i++) {
			if (bumpies[i].uid == -1) {
				continue;
			}
			if (bumpies[i].shading_mode == 0) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(bumpies[i].color));
			glStencilFunc(GL_ALWAYS, bumpies[i].uid, -1);

			VBO.update(bumpies[i].posvec);
			ebo.update(bumpies[i].indvec);
			auto model = glm::translate(glm::mat4(1.0f), bumpies[i].modelpos);
			model = glm::rotate(model, bumpies[i].angleY, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, bumpies[i].angleX, glm::vec3(1.0f, 0.0f, 0.0f));
			float objsize = bumpies[i].objsize;
			model = glm::scale(model, glm::vec3(objsize, objsize, objsize));

			glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, bumpies[i].indcount, GL_UNSIGNED_INT, (GLvoid*)((bumpies[i].indstart) * sizeof(GL_UNSIGNED_INT)));
		}

		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		check_gl_error();
	 

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		program.bind();

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTexture);*/

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glUniform1i(program.uniform("shadowMap"), 1);
		

		glUniformMatrix4fv(program.uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
 
		glUniform3fv(program.uniform("lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(program.uniform("viewPos"), 1, glm::value_ptr(viewPos));
		glUniform3fv(program.uniform("lightPos"),1, glm::value_ptr(lightPos));
		glUniform1i(program.uniform("shading_mode"), shading_mode);
		//env map
		glUniform1i(program.uniform("skybox"), 0);
		
		glm::vec3 cameraPos(0.0f, 4.0f, 0.0f);
		glUniform3fv(program.uniform("cameraPos"), 1, glm::value_ptr(cameraPos));

        glUniformMatrix4fv(program.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
		
	
		check_gl_error();
    
		glUniform1i(program.uniform("redon"), redShade);
		glUniform1i(program.uniform("display_mode"), 2);
		glUniform1i(program.uniform("mode"), 1);
		glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(glm::vec3(0.73f)));
		VBO.update(plane[0].posvec);
		ebo.update(plane[0].indvec);
		glUniform1i(program.uniform("mode"), 1);
		glStencilFunc(GL_ALWAYS, 150, -1);
		auto model1 = glm::scale(glm::mat4(1.0f), glm::vec3(1,1,1));
		glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model1));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glUniform1i(program.uniform("display_mode"), 0);
		glActiveTexture(GL_TEXTURE0);
        glUniform1i(program.uniform("mode"), 0);
        for (int i = 0; i < cubes.size(); i++){
			if (cubes[i].uid == -1) {
				continue;
			}
			if (cubes[i].shading_mode == 0){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			if (cubes[i].uid == globalPickedId){
				glUniform1i(program.uniform("mode"), 2);
			}else{
				glUniform1i(program.uniform("mode"), cubes[i].mode);
			}
			
			glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(cubes[i].color));
			glStencilFunc(GL_ALWAYS, cubes[i].uid, -1);	
			VBO.update(cubes[i].posvec);
			ebo.update(cubes[i].ind);
			auto model = glm::translate(glm::mat4(1.0f), cubes[i].modelpos);
			model = glm::rotate(model, cubes[i].angleY, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, cubes[i].angleX, glm::vec3(1.0f, 0.0f, 0.0f));
			float objsize = cubes[i].objsize;
			model = glm::scale(model, glm::vec3(objsize, objsize, objsize));
			glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			// std::cout << cubes[i].posvec.size() << std::endl;
        }


        for (int i = 0; i < bunnies.size();i++){      
			if (bunnies[i].uid == -1) {
				continue;
			}

			if (bunnies[i].shading_mode == 0){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(bunnies[i].color));
			glStencilFunc(GL_ALWAYS, bunnies[i].uid, -1);	
			if (bunnies[i].uid == globalPickedId){
				glUniform1i(program.uniform("mode"), 2);
			}else{
				glUniform1i(program.uniform("mode"), bunnies[i].mode);
			}

			VBO.update(bunnies[i].posvec);
			ebo.update(bunnies[i].indvec);
			auto model = glm::translate(glm::mat4(1.0f), bunnies[i].modelpos);
			model = glm::rotate(model, bunnies[i].angleY, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, bunnies[i].angleX, glm::vec3(1.0f, 0.0f, 0.0f));
			float objsize = bunnies[i].objsize;
			model = glm::scale(model, glm::vec3(objsize, objsize, objsize));
			glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, (0));
	
        }

        for (int i = 0; i < bumpies.size();i++){     
			if (bumpies[i].uid == -1) {
				continue;
			}
			if (bumpies[i].shading_mode == 0){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			glUniform3fv(program.uniform("objectColor"), 1, glm::value_ptr(bumpies[i].color));
			// std::cout << bumpies[i].color.y << std::endl;
			glStencilFunc(GL_ALWAYS, bumpies[i].uid, -1);
			if (bumpies[i].uid == globalPickedId){
				glUniform1i(program.uniform("mode"), 2);
			}else{
				glUniform1i(program.uniform("mode"), bumpies[i].mode);
			}
		
			VBO.update(bumpies[i].posvec);
			ebo.update(bumpies[i].indvec);
			auto model = glm::translate(glm::mat4(1.0f), bumpies[i].modelpos);
			model = glm::rotate(model, bumpies[i].angleY, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, bumpies[i].angleX, glm::vec3(1.0f, 0.0f, 0.0f));
			float objsize = bumpies[i].objsize;
			model = glm::scale(model, glm::vec3(objsize, objsize, objsize));

			glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, bumpies[i].indcount, GL_UNSIGNED_INT, (GLvoid*)((bumpies[i].indstart)*sizeof(GL_UNSIGNED_INT)));
        }
		// cubeBoxProgram.bind();
		// glUniform1i(cubeBoxProgram.uniform("skybox"), 0);
		// glUniformMatrix4fv(cubeBoxProgram.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
		// glUniformMatrix4fv(cubeBoxProgram.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
		// glUniformMatrix4fv(cubeBoxProgram.uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// //glm::vec3 cameraPos(0.0f, 4.0f, 0.0f);
		// glUniform3fv(cubeBoxProgram.uniform("cameraPos"), 1, glm::value_ptr(cameraPos));
		// glBindVertexArray(cubeVAO);
		// check_gl_error();
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		// //glDrawArrays(GL_TRIANGLES, 0, 36);
		// glBindVertexArray(0);

		programShading.bind();

	 	view = glm::lookAt(platform,glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0,1.0,0.0));


		glUniformMatrix4fv(programShading.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(programShading.uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));


		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

		// skybox cube
		glBindVertexArray(skyboxVAO);
		check_gl_error();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
	

    // Deallocate opengl memory
    program.free();
    VAO.free();
    VBO.free();
    ebo.free();

    // Deallocate glfw internals
    glfwTerminate();
    return 0;
}

