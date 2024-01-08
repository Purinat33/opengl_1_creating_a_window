# OpenGL Tutorial 1: Introduction and creating a window.

`OpenGL` is basically specification.

We use implementations by others to meet up these specification.

We normally use **OpenGL Core 3.3.X** because newer version might not be supported and Core specifications are basically the same every version with slight adjustments anyway.

## OpenGL's States

OpenGL is by itself a large state machine: a collection of variables that define how OpenGL should currently operate. The state of OpenGL is commonly referred to as the OpenGL **context**. When using OpenGL, we often change its state by setting some options, manipulating some buffers and then render using the current context.

Whenever we tell OpenGL that we now want to draw lines instead of triangles for example, we change the state of OpenGL by changing some context variable that sets how OpenGL should draw. As soon as we change the context by telling OpenGL it should draw lines, the next drawing commands will now draw lines instead of triangles.

When working in OpenGL we will come across several state-changing functions that change the context and several state-using functions that perform some operations based on the current state of OpenGL. As long as you keep in mind that OpenGL is basically one large state machine, most of its functionality will make more sense.

## OpenGL's Objects
An object in OpenGL is a collection of options that represents a subset of OpenGL's state. For example, we could have an object that represents the settings of the drawing window; we could then set its size, how many colors it supports and so on. One could visualize an object as a C-like struct:

Example:
```C++
// create object
unsigned int objectId = 0;
glGenObject(1, &objectId);
// bind/assign object to context
glBindObject(GL_WINDOW_TARGET, objectId);
// set options of object currently bound to GL_WINDOW_TARGET
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH,  800);
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
// set context target back to default
glBindObject(GL_WINDOW_TARGET, 0);
```

1. Create an object and store a reference to it as an id (the real object's data is stored behind the scenes).
2. we bind the object (using its id) to the target location of the context (the location of the example window object target is defined as `GL_WINDOW_TARGET`).
3. we set the window options and finally we un-bind the object by setting the current object id of the window target to 0
4. The options we set are stored in the object referenced by `objectId` and restored as soon as we bind the object back to `GL_WINDOW_TARGET`.

### Binding
Binding is like passing settings of an object to a context. Unbinding is not using those settings.

For example:

* Object A: Contains settings for rendering a house (e.g., its size, texture, color).

* Object B: Contains settings for rendering a human (e.g., skeletal structure, skin tone, clothing).

When you want to draw a house, you would bind Object A to the drawing context by associating it with the appropriate target within the OpenGL context. This means that all the settings defined in Object A will be applied to the rendering process without needing to redefine them every time you draw the house.

Likewise, if you want to switch to drawing a human, you would simply bind Object B to the context. This way, the previously defined settings for the human model will be applied, allowing you to render the human without reconfiguring all the settings manually.

