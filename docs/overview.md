# OpenGL Overview

- [OpenGL Overview](#opengl-overview)
  - [What is OpenGL?](#what-is-opengl)
  - [OpenGL Context](#opengl-context)
  - [OpenGL Versions](#opengl-versions)

## What is OpenGL?

OpenGL is a graphics API that allows us to interact with the GPU. It is a specification, not an implementation. This means that the OpenGL functions are not implemented in the OpenGL library. Instead, they are implemented in the graphics driver. This means that we need to load the functions from the graphics driver. This is done using an opengl loading library such as: GLEW, GLAD, etc.

Normally, when you define an object in a language like C or C++, you would do this:

```c++
// Define the object interface
struct Entity {
    uint32_t m_ID;
    const char* m_Name;
    struct Properties props;
};

// Create an instance
Entity newEntity;

// Put data into the instance
newEntity.m_ID = 0;
newEntity.m_Name = "Entity";
newEntity.props = { 0, 0, 0 };
```

In OpenGL you would do something like this:

```c++
// These are not actual OpenGL functions, they are just a demo

// create the object instance
GLuint entity;
glGenObjects(1, &entity);

// Put data into the instance
glObjectParameteri(GL_MODIFY, GL_OBJECT_COUNT, 5);
glObjectParameterf(GL_MODIFY, GL_OBJECT_OPACITY, 0.4f);
glObjectParameters(GL_MODIFY, GL_OBJECT_NAME, "Some String");
```

## OpenGL Context

The OpenGL API is defined as a state machine. Almost all of the OpenGL functions set or retrieve some state in OpenGL. The only functions that do not change state are functions that use the currently set state to cause rendering to happen.

You can think of the state machine as a very large struct with a great many different fields. This struct is called the **OpenGL context**, and each field in the context represents some information necessary for rendering.

Objects in OpenGL are thus defined as a list of fields in this struct that can be saved and restored. This is done using the `glPushAttrib` and `glPopAttrib` functions.

**Binding** an object to a target within the context causes the data in this object to replace some of the context's state. Thus after the binding, future function calls that read from or modify this context state will read or modify the state within the object. This is done using the `glBind*` functions.

Objects are usually represented as GLuint integers; these are handles to the actual OpenGL objects. The integer value 0 is special; it acts as the object equivalent of a NULL pointer. Binding object 0 means to unbind the currently bound object. This means that the original context state, the state that was in place before the binding took place, now becomes the context state.

```c++
// Create a new vertex array object
GLuint vao;
glGenVertexArrays(1, &vao);

// Bind the vertex array object
glBindVertexArray(vao);

// Do some stuff with the vertex array object
glDrawArrays(GL_TRIANGLES, 0, 3);

// Unbind the vertex array object
glBindVertexArray(0);
```

In the previous example, we created a vertex array object and bound it to the context. We then used the vertex array object to draw a triangle. After we were done drawing the triangle, we unbound the vertex array object.

## OpenGL Versions

Code that works on one version of OpenGL will almost always work on later versions of OpenGL.

The only exception to this deals with OpenGL 3.0 and above, relative to previous versions. v3.0 deprecated a number of older functions, and v3.1 removed most of those functions from the API. This also divided the specification into 2 variations (called **profiles**): core and compatibility. 

- The compatibility profile retains all of the functions removed in 3.1.
- The core profile does not.

Theoretically, OpenGL implementations could implement just the core profile; this would leave software that relies on the compatibility profile non-functional on that implementation.

In practice, all implementations that support OpenGL 3.0 and above support both profiles. This means that you can use the core profile and still use all of the functions that were removed in 3.1. This is done by creating a context with the core profile, and then enabling the compatibility profile.

---

Next: [The Rendering Pipeline](rendering-pipeline.md)
