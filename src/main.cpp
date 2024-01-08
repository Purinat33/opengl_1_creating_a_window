// Creating a window in OpenGL
// Intro to libraries

// GLAD
/*
Because OpenGL is only really a standard/specification it is up to the driver manufacturer to implement the specification to a driver that the specific graphics card supports. Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time
*/

// GLFW
/*
GLFW gives us the bare necessities required for rendering goodies to the screen. It allows us to create an OpenGL context, define window parameters, and handle user input, which is plenty enough for our purposes.
*/

// include GLAD before GLFW
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>

// callback function on the window that gets called each time the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// function to check for key press
void processInput(GLFWwindow* window);

int main()
{
    // Initialize the GLFW library, most functions required GLFW to be init() first
    glfwInit();
    // Telling that we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Telling that we are using Core-Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MacOS only
    // Note that on Mac OS X you need to add glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); to your initialization code for it to work.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creating the Window
    int width{800};
    int height{600};
    // monitor (NULL for windowed mode)
    // share (share resources?)
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Window Creation Failed\n";
        glfwTerminate(); // Free all resources
        return -1;
    }

    // Make this window the current context (can only have one at a time per thread)
    glfwMakeContextCurrent(window); 

    // GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function:
    // Check if GLAD exists
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialized GLAD\n";
        return -1; 
    }

    // Viewport
    // We have to tell OpenGL the size of the rendering window so OpenGL knows how we want to display the data and coordinates with respect to the window. We can set those dimensions via the glViewport function:
    glViewport(0, 0, width, height); 
    // 0, 0 means we use the entire window we created
    // or basically "start from bottom left of the window"

    // Note
    /*
    Behind the scenes OpenGL uses the data specified via glViewport to transform the 2D coordinates it processed to coordinates on your screen.
    For example, a processed point of location (-0.5,0.5) would (as its final transformation) be mapped to (200,450) in screen coordinates. 
    Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).
    */

    // However, the moment a user resizes the window the viewport should be adjusted as well. We can register a callback function on the window that gets called each time the window is resized. This resize callback function has the following prototype:
    // void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    // Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for you to process.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // We can use callback functions other than for window resizing
    // we can make a callback function to process joystick input changes, process error messages etc. 
    // We register the callback functions after we've created the window and before the render loop is initiated.


    // THE RENDER LOOP (running forever until we stop)
    while(!glfwWindowShouldClose(window)){

        // Check for key press
        processInput(window);

        // Rendering command
        // ...
        //
        // At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame
        
        // Set the color value that will be used when glClear is called
        glClearColor(0.5f, 0.2f, 0.3f, 1.0f); // SET State
        // Use the state (as defined in glClearColor)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // loop end
        // Swap front and back buffer
        // Before rendering to the screen
        // Things are drawn on the buffers
        // We display front while we draw back
        // and vice versa, keep swapping
        glfwSwapBuffers(window);

        /*

        The front buffer contains the final output image that is shown at the screen, 
        while all the rendering commands draw to the back buffer. 
        As soon as all the rendering commands are finished we swap the back buffer to the front buffer so the image can be displayed without still being rendered to

        */

        // checks if any events are triggered (like keyboard input or mouse movement events), updates the window state, and calls the corresponding functions (which we can register via callback methods).
        glfwPollEvents();
    }

    // Properly terminate GLFW resources
    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0, width, height);
}


// Processing keyboard input
// Checking for keypress
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
