/*
 * bindings.cc
 *
 *  Created on: Dec 13, 2011
 *      Author: ngk437
 *
 * Modified by Mikola Lysenko, Feb. 2013
 */

#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif

#include <cstdlib>
#include <v8.h>
#include <node.h>

#include "webgl.h"

using namespace v8;

Persistent<FunctionTemplate> webgl_template;

#define JS_SET_GL_CONSTANT(tmpl, name) tmpl->Set(NanNew<String>(#name), NanNew<Integer>(GL_ ## name))
#define JS_SET_NUM_CONSTANT(tmpl, name, val) tmpl->Set(NanNew<String>(name), NanNew<Integer>(val))
#define JS_SET_METHOD(tmpl, name, fn) NODE_SET_PROTOTYPE_METHOD(tmpl, name, fn)

namespace HeadlessGL {

void Init(Handle<Object> target) {
  // When node exits kill any stray gl contexts
  atexit(WebGL::disposeAll);

  // Create the WebGL template
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(WebGL::New);
  NanAssignPersistent(webgl_template, tpl);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  tpl->SetClassName(NanNew<String>("WebGLRenderingContext"));

  //Add methods
  Handle<ObjectTemplate> proto = tpl->PrototypeTemplate();
  JS_SET_METHOD(tpl, "uniform1f", WebGL::Uniform1f);
  JS_SET_METHOD(tpl, "uniform2f", WebGL::Uniform2f);
  JS_SET_METHOD(tpl, "uniform3f", WebGL::Uniform3f);
  JS_SET_METHOD(tpl, "uniform4f", WebGL::Uniform4f);
  JS_SET_METHOD(tpl, "uniform1i", WebGL::Uniform1i);
  JS_SET_METHOD(tpl, "uniform2i", WebGL::Uniform2i);
  JS_SET_METHOD(tpl, "uniform3i", WebGL::Uniform3i);
  JS_SET_METHOD(tpl, "uniform4i", WebGL::Uniform4i);
  JS_SET_METHOD(tpl, "uniform1fv", WebGL::Uniform1fv);
  JS_SET_METHOD(tpl, "uniform2fv", WebGL::Uniform2fv);
  JS_SET_METHOD(tpl, "uniform3fv", WebGL::Uniform3fv);
  JS_SET_METHOD(tpl, "uniform4fv", WebGL::Uniform4fv);
  JS_SET_METHOD(tpl, "uniform1iv", WebGL::Uniform1iv);
  JS_SET_METHOD(tpl, "uniform2iv", WebGL::Uniform2iv);
  JS_SET_METHOD(tpl, "uniform3iv", WebGL::Uniform3iv);
  JS_SET_METHOD(tpl, "uniform4iv", WebGL::Uniform4iv);
  JS_SET_METHOD(tpl, "pixelStorei", WebGL::PixelStorei);
  JS_SET_METHOD(tpl, "bindAttribLocation", WebGL::BindAttribLocation);
  JS_SET_METHOD(tpl, "getError", WebGL::GetError);
  JS_SET_METHOD(tpl, "drawArrays", WebGL::DrawArrays);
  JS_SET_METHOD(tpl, "uniformMatrix2fv", WebGL::UniformMatrix2fv);
  JS_SET_METHOD(tpl, "uniformMatrix3fv", WebGL::UniformMatrix3fv);
  JS_SET_METHOD(tpl, "uniformMatrix4fv", WebGL::UniformMatrix4fv);

  JS_SET_METHOD(tpl, "generateMipmap", WebGL::GenerateMipmap);

  JS_SET_METHOD(tpl, "getAttribLocation", WebGL::GetAttribLocation);
  JS_SET_METHOD(tpl, "depthFunc", WebGL::DepthFunc);
  JS_SET_METHOD(tpl, "viewport", WebGL::Viewport);
  JS_SET_METHOD(tpl, "createShader", WebGL::CreateShader);
  JS_SET_METHOD(tpl, "shaderSource", WebGL::ShaderSource);
  JS_SET_METHOD(tpl, "compileShader", WebGL::CompileShader);
  JS_SET_METHOD(tpl, "getShaderParameter", WebGL::GetShaderParameter);
  JS_SET_METHOD(tpl, "getShaderInfoLog", WebGL::GetShaderInfoLog);
  JS_SET_METHOD(tpl, "createProgram", WebGL::CreateProgram);
  JS_SET_METHOD(tpl, "attachShader", WebGL::AttachShader);
  JS_SET_METHOD(tpl, "linkProgram", WebGL::LinkProgram);
  JS_SET_METHOD(tpl, "getProgramParameter", WebGL::GetProgramParameter);
  JS_SET_METHOD(tpl, "getUniformLocation", WebGL::GetUniformLocation);
  JS_SET_METHOD(tpl, "clearColor", WebGL::ClearColor);
  JS_SET_METHOD(tpl, "clearDepth", WebGL::ClearDepth);

  JS_SET_METHOD(tpl, "disable", WebGL::Disable);
  JS_SET_METHOD(tpl, "createTexture", WebGL::CreateTexture);
  JS_SET_METHOD(tpl, "bindTexture", WebGL::BindTexture);
  JS_SET_METHOD(tpl, "texImage2D", WebGL::TexImage2D);
  JS_SET_METHOD(tpl, "texParameteri", WebGL::TexParameteri);
  JS_SET_METHOD(tpl, "texParameterf", WebGL::TexParameterf);
  JS_SET_METHOD(tpl, "clear", WebGL::Clear);
  JS_SET_METHOD(tpl, "useProgram", WebGL::UseProgram);
  JS_SET_METHOD(tpl, "createFramebuffer", WebGL::CreateFramebuffer);
  JS_SET_METHOD(tpl, "bindFramebuffer", WebGL::BindFramebuffer);
  JS_SET_METHOD(tpl, "framebufferTexture2D", WebGL::FramebufferTexture2D);
  JS_SET_METHOD(tpl, "createBuffer", WebGL::CreateBuffer);
  JS_SET_METHOD(tpl, "bindBuffer", WebGL::BindBuffer);
  JS_SET_METHOD(tpl, "bufferData", WebGL::BufferData);
  JS_SET_METHOD(tpl, "bufferSubData", WebGL::BufferSubData);
  JS_SET_METHOD(tpl, "enable", WebGL::Enable);
  JS_SET_METHOD(tpl, "blendEquation", WebGL::BlendEquation);
  JS_SET_METHOD(tpl, "blendFunc", WebGL::BlendFunc);
  JS_SET_METHOD(tpl, "enableVertexAttribArray", WebGL::EnableVertexAttribArray);
  JS_SET_METHOD(tpl, "vertexAttribPointer", WebGL::VertexAttribPointer);
  JS_SET_METHOD(tpl, "activeTexture", WebGL::ActiveTexture);
  JS_SET_METHOD(tpl, "drawElements", WebGL::DrawElements);
  JS_SET_METHOD(tpl, "flush", WebGL::Flush);
  JS_SET_METHOD(tpl, "finish", WebGL::Finish);

  JS_SET_METHOD(tpl, "vertexAttrib1f", WebGL::VertexAttrib1f);
  JS_SET_METHOD(tpl, "vertexAttrib2f", WebGL::VertexAttrib2f);
  JS_SET_METHOD(tpl, "vertexAttrib3f", WebGL::VertexAttrib3f);
  JS_SET_METHOD(tpl, "vertexAttrib4f", WebGL::VertexAttrib4f);
  JS_SET_METHOD(tpl, "vertexAttrib1fv", WebGL::VertexAttrib1fv);
  JS_SET_METHOD(tpl, "vertexAttrib2fv", WebGL::VertexAttrib2fv);
  JS_SET_METHOD(tpl, "vertexAttrib3fv", WebGL::VertexAttrib3fv);
  JS_SET_METHOD(tpl, "vertexAttrib4fv", WebGL::VertexAttrib4fv);

  JS_SET_METHOD(tpl, "blendColor", WebGL::BlendColor);
  JS_SET_METHOD(tpl, "blendEquationSeparate", WebGL::BlendEquationSeparate);
  JS_SET_METHOD(tpl, "blendFuncSeparate", WebGL::BlendFuncSeparate);
  JS_SET_METHOD(tpl, "clearStencil", WebGL::ClearStencil);
  JS_SET_METHOD(tpl, "colorMask", WebGL::ColorMask);
  JS_SET_METHOD(tpl, "copyTexImage2D", WebGL::CopyTexImage2D);
  JS_SET_METHOD(tpl, "copyTexSubImage2D", WebGL::CopyTexSubImage2D);
  JS_SET_METHOD(tpl, "cullFace", WebGL::CullFace);
  JS_SET_METHOD(tpl, "depthMask", WebGL::DepthMask);
  JS_SET_METHOD(tpl, "depthRange", WebGL::DepthRange);
  JS_SET_METHOD(tpl, "disableVertexAttribArray", WebGL::DisableVertexAttribArray);
  JS_SET_METHOD(tpl, "hint", WebGL::Hint);
  JS_SET_METHOD(tpl, "isEnabled", WebGL::IsEnabled);
  JS_SET_METHOD(tpl, "lineWidth", WebGL::LineWidth);
  JS_SET_METHOD(tpl, "polygonOffset", WebGL::PolygonOffset);

  JS_SET_METHOD(tpl, "scissor", WebGL::Scissor);
  JS_SET_METHOD(tpl, "stencilFunc", WebGL::StencilFunc);
  JS_SET_METHOD(tpl, "stencilFuncSeparate", WebGL::StencilFuncSeparate);
  JS_SET_METHOD(tpl, "stencilMask", WebGL::StencilMask);
  JS_SET_METHOD(tpl, "stencilMaskSeparate", WebGL::StencilMaskSeparate);
  JS_SET_METHOD(tpl, "stencilOp", WebGL::StencilOp);
  JS_SET_METHOD(tpl, "stencilOpSeparate", WebGL::StencilOpSeparate);
  JS_SET_METHOD(tpl, "bindRenderbuffer", WebGL::BindRenderbuffer);
  JS_SET_METHOD(tpl, "createRenderbuffer", WebGL::CreateRenderbuffer);

  JS_SET_METHOD(tpl, "deleteBuffer", WebGL::DeleteBuffer);
  JS_SET_METHOD(tpl, "deleteFramebuffer", WebGL::DeleteFramebuffer);
  JS_SET_METHOD(tpl, "deleteProgram", WebGL::DeleteProgram);
  JS_SET_METHOD(tpl, "deleteRenderbuffer", WebGL::DeleteRenderbuffer);
  JS_SET_METHOD(tpl, "deleteShader", WebGL::DeleteShader);
  JS_SET_METHOD(tpl, "deleteTexture", WebGL::DeleteTexture);
  JS_SET_METHOD(tpl, "detachShader", WebGL::DetachShader);
  JS_SET_METHOD(tpl, "framebufferRenderbuffer", WebGL::FramebufferRenderbuffer);
  JS_SET_METHOD(tpl, "getVertexAttribOffset", WebGL::GetVertexAttribOffset);

  JS_SET_METHOD(tpl, "isBuffer", WebGL::IsBuffer);
  JS_SET_METHOD(tpl, "isFramebuffer", WebGL::IsFramebuffer);
  JS_SET_METHOD(tpl, "isProgram", WebGL::IsProgram);
  JS_SET_METHOD(tpl, "isRenderbuffer", WebGL::IsRenderbuffer);
  JS_SET_METHOD(tpl, "isShader", WebGL::IsShader);
  JS_SET_METHOD(tpl, "isTexture", WebGL::IsTexture);

  JS_SET_METHOD(tpl, "renderbufferStorage", WebGL::RenderbufferStorage);
  JS_SET_METHOD(tpl, "getShaderSource", WebGL::GetShaderSource);
  JS_SET_METHOD(tpl, "validateProgram", WebGL::ValidateProgram);

  JS_SET_METHOD(tpl, "texSubImage2D", WebGL::TexSubImage2D);
  JS_SET_METHOD(tpl, "readPixels", WebGL::ReadPixels);
  JS_SET_METHOD(tpl, "getTexParameter", WebGL::GetTexParameter);
  JS_SET_METHOD(tpl, "getActiveAttrib", WebGL::GetActiveAttrib);
  JS_SET_METHOD(tpl, "getActiveUniform", WebGL::GetActiveUniform);
  JS_SET_METHOD(tpl, "getAttachedShaders", WebGL::GetAttachedShaders);
  JS_SET_METHOD(tpl, "getParameter", WebGL::GetParameter);
  JS_SET_METHOD(tpl, "getBufferParameter", WebGL::GetBufferParameter);
  JS_SET_METHOD(tpl, "getFramebufferAttachmentParameter", WebGL::GetFramebufferAttachmentParameter);
  JS_SET_METHOD(tpl, "getProgramInfoLog", WebGL::GetProgramInfoLog);
  JS_SET_METHOD(tpl, "getRenderbufferParameter", WebGL::GetRenderbufferParameter);
  JS_SET_METHOD(tpl, "getVertexAttrib", WebGL::GetVertexAttrib);
  JS_SET_METHOD(tpl, "getSupportedExtensions", WebGL::GetSupportedExtensions);
  JS_SET_METHOD(tpl, "getExtension", WebGL::GetExtension);
  JS_SET_METHOD(tpl, "checkFramebufferStatus", WebGL::CheckFramebufferStatus);

  JS_SET_METHOD(tpl, "frontFace", WebGL::FrontFace);
  JS_SET_METHOD(tpl, "sampleCoverage", WebGL::SampleCoverage);
  JS_SET_METHOD(tpl, "destroy", WebGL::Destroy);


  // OpenGL ES 2.1 constants

  /* ClearBufferMask */
  JS_SET_GL_CONSTANT(proto, DEPTH_BUFFER_BIT);
  JS_SET_GL_CONSTANT(proto, STENCIL_BUFFER_BIT);
  JS_SET_GL_CONSTANT(proto, COLOR_BUFFER_BIT);

  /* Boolean */
  JS_SET_GL_CONSTANT(proto, FALSE);
  JS_SET_GL_CONSTANT(proto, TRUE);

  /* BeginMode */
  JS_SET_GL_CONSTANT(proto, POINTS);
  JS_SET_GL_CONSTANT(proto, LINES);
  JS_SET_GL_CONSTANT(proto, LINE_LOOP);
  JS_SET_GL_CONSTANT(proto, LINE_STRIP);
  JS_SET_GL_CONSTANT(proto, TRIANGLES);
  JS_SET_GL_CONSTANT(proto, TRIANGLE_STRIP);
  JS_SET_GL_CONSTANT(proto, TRIANGLE_FAN);

  /* AlphaFunction (not supported in ES20) */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* BlendingFactorDest */
  JS_SET_GL_CONSTANT(proto, ZERO);
  JS_SET_GL_CONSTANT(proto, ONE);
  JS_SET_GL_CONSTANT(proto, SRC_COLOR);
  JS_SET_GL_CONSTANT(proto, ONE_MINUS_SRC_COLOR);
  JS_SET_GL_CONSTANT(proto, SRC_ALPHA);
  JS_SET_GL_CONSTANT(proto, ONE_MINUS_SRC_ALPHA);
  JS_SET_GL_CONSTANT(proto, DST_ALPHA);
  JS_SET_GL_CONSTANT(proto, ONE_MINUS_DST_ALPHA);

  /* BlendingFactorSrc */
  /*      GL_ZERO */
  /*      GL_ONE */
  JS_SET_GL_CONSTANT(proto, DST_COLOR);
  JS_SET_GL_CONSTANT(proto, ONE_MINUS_DST_COLOR);
  JS_SET_GL_CONSTANT(proto, SRC_ALPHA_SATURATE);
  /*      GL_SRC_ALPHA */
  /*      GL_ONE_MINUS_SRC_ALPHA */
  /*      GL_DST_ALPHA */
  /*      GL_ONE_MINUS_DST_ALPHA */

  /* BlendEquationSeparate */
  JS_SET_GL_CONSTANT(proto, FUNC_ADD);
  JS_SET_GL_CONSTANT(proto, BLEND_EQUATION);
  JS_SET_GL_CONSTANT(proto, BLEND_EQUATION_RGB);    /* same as BLEND_EQUATION */
  JS_SET_GL_CONSTANT(proto, BLEND_EQUATION_ALPHA);

  /* BlendSubtract */
  JS_SET_GL_CONSTANT(proto, FUNC_SUBTRACT);
  JS_SET_GL_CONSTANT(proto, FUNC_REVERSE_SUBTRACT);

  /* Separate Blend Functions */
  JS_SET_GL_CONSTANT(proto, BLEND_DST_RGB);
  JS_SET_GL_CONSTANT(proto, BLEND_SRC_RGB);
  JS_SET_GL_CONSTANT(proto, BLEND_DST_ALPHA);
  JS_SET_GL_CONSTANT(proto, BLEND_SRC_ALPHA);
  JS_SET_GL_CONSTANT(proto, CONSTANT_COLOR);
  JS_SET_GL_CONSTANT(proto, ONE_MINUS_CONSTANT_COLOR);
  JS_SET_GL_CONSTANT(proto, CONSTANT_ALPHA);
  JS_SET_GL_CONSTANT(proto, ONE_MINUS_CONSTANT_ALPHA);
  JS_SET_GL_CONSTANT(proto, BLEND_COLOR);

  /* Buffer Objects */
  JS_SET_GL_CONSTANT(proto, ARRAY_BUFFER);
  JS_SET_GL_CONSTANT(proto, ELEMENT_ARRAY_BUFFER);
  JS_SET_GL_CONSTANT(proto, ARRAY_BUFFER_BINDING);
  JS_SET_GL_CONSTANT(proto, ELEMENT_ARRAY_BUFFER_BINDING);

  JS_SET_GL_CONSTANT(proto, STREAM_DRAW);
  JS_SET_GL_CONSTANT(proto, STATIC_DRAW);
  JS_SET_GL_CONSTANT(proto, DYNAMIC_DRAW);

  JS_SET_GL_CONSTANT(proto, BUFFER_SIZE);
  JS_SET_GL_CONSTANT(proto, BUFFER_USAGE);

  JS_SET_GL_CONSTANT(proto, CURRENT_VERTEX_ATTRIB);

  /* CullFaceMode */
  JS_SET_GL_CONSTANT(proto, FRONT);
  JS_SET_GL_CONSTANT(proto, BACK);
  JS_SET_GL_CONSTANT(proto, FRONT_AND_BACK);

  /* DepthFunction */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* EnableCap */
  JS_SET_GL_CONSTANT(proto, TEXTURE_2D);
  JS_SET_GL_CONSTANT(proto, CULL_FACE);
  JS_SET_GL_CONSTANT(proto, BLEND);
  JS_SET_GL_CONSTANT(proto, DITHER);
  JS_SET_GL_CONSTANT(proto, STENCIL_TEST);
  JS_SET_GL_CONSTANT(proto, DEPTH_TEST);
  JS_SET_GL_CONSTANT(proto, SCISSOR_TEST);
  JS_SET_GL_CONSTANT(proto, POLYGON_OFFSET_FILL);
  JS_SET_GL_CONSTANT(proto, SAMPLE_ALPHA_TO_COVERAGE);
  JS_SET_GL_CONSTANT(proto, SAMPLE_COVERAGE);

  /* ErrorCode */
  JS_SET_GL_CONSTANT(proto, NO_ERROR);
  JS_SET_GL_CONSTANT(proto, INVALID_ENUM);
  JS_SET_GL_CONSTANT(proto, INVALID_VALUE);
  JS_SET_GL_CONSTANT(proto, INVALID_OPERATION);
  JS_SET_GL_CONSTANT(proto, OUT_OF_MEMORY);

  /* FrontFaceDirection */
  JS_SET_GL_CONSTANT(proto, CW);
  JS_SET_GL_CONSTANT(proto, CCW);

  /* GetPName */
  JS_SET_GL_CONSTANT(proto, LINE_WIDTH);
  JS_SET_GL_CONSTANT(proto, ALIASED_POINT_SIZE_RANGE);
  JS_SET_GL_CONSTANT(proto, ALIASED_LINE_WIDTH_RANGE);
  JS_SET_GL_CONSTANT(proto, CULL_FACE_MODE);
  JS_SET_GL_CONSTANT(proto, FRONT_FACE);
  JS_SET_GL_CONSTANT(proto, DEPTH_RANGE);
  JS_SET_GL_CONSTANT(proto, DEPTH_WRITEMASK);
  JS_SET_GL_CONSTANT(proto, DEPTH_CLEAR_VALUE);
  JS_SET_GL_CONSTANT(proto, DEPTH_FUNC);
  JS_SET_GL_CONSTANT(proto, STENCIL_CLEAR_VALUE);
  JS_SET_GL_CONSTANT(proto, STENCIL_FUNC);
  JS_SET_GL_CONSTANT(proto, STENCIL_FAIL);
  JS_SET_GL_CONSTANT(proto, STENCIL_PASS_DEPTH_FAIL);
  JS_SET_GL_CONSTANT(proto, STENCIL_PASS_DEPTH_PASS);
  JS_SET_GL_CONSTANT(proto, STENCIL_REF);
  JS_SET_GL_CONSTANT(proto, STENCIL_VALUE_MASK);
  JS_SET_GL_CONSTANT(proto, STENCIL_WRITEMASK);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_FUNC);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_FAIL);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_PASS_DEPTH_FAIL);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_PASS_DEPTH_PASS);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_REF);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_VALUE_MASK);
  JS_SET_GL_CONSTANT(proto, STENCIL_BACK_WRITEMASK);
  JS_SET_GL_CONSTANT(proto, VIEWPORT);
  JS_SET_GL_CONSTANT(proto, SCISSOR_BOX);
  /*      GL_SCISSOR_TEST */
  JS_SET_GL_CONSTANT(proto, COLOR_CLEAR_VALUE);
  JS_SET_GL_CONSTANT(proto, COLOR_WRITEMASK);
  JS_SET_GL_CONSTANT(proto, UNPACK_ALIGNMENT);
  JS_SET_GL_CONSTANT(proto, PACK_ALIGNMENT);
  JS_SET_GL_CONSTANT(proto, MAX_TEXTURE_SIZE);
  JS_SET_GL_CONSTANT(proto, MAX_VIEWPORT_DIMS);
  JS_SET_GL_CONSTANT(proto, SUBPIXEL_BITS);
  JS_SET_GL_CONSTANT(proto, RED_BITS);
  JS_SET_GL_CONSTANT(proto, GREEN_BITS);
  JS_SET_GL_CONSTANT(proto, BLUE_BITS);
  JS_SET_GL_CONSTANT(proto, ALPHA_BITS);
  JS_SET_GL_CONSTANT(proto, DEPTH_BITS);
  JS_SET_GL_CONSTANT(proto, STENCIL_BITS);
  JS_SET_GL_CONSTANT(proto, POLYGON_OFFSET_UNITS);
  /*      GL_POLYGON_OFFSET_FILL */
  JS_SET_GL_CONSTANT(proto, POLYGON_OFFSET_FACTOR);
  JS_SET_GL_CONSTANT(proto, TEXTURE_BINDING_2D);
  JS_SET_GL_CONSTANT(proto, SAMPLE_BUFFERS);
  JS_SET_GL_CONSTANT(proto, SAMPLES);
  JS_SET_GL_CONSTANT(proto, SAMPLE_COVERAGE_VALUE);
  JS_SET_GL_CONSTANT(proto, SAMPLE_COVERAGE_INVERT);

  /* GetTextureParameter */
  /*      GL_TEXTURE_MAG_FILTER */
  /*      GL_TEXTURE_MIN_FILTER */
  /*      GL_TEXTURE_WRAP_S */
  /*      GL_TEXTURE_WRAP_T */

  JS_SET_GL_CONSTANT(proto, NUM_COMPRESSED_TEXTURE_FORMATS);
  JS_SET_GL_CONSTANT(proto, COMPRESSED_TEXTURE_FORMATS);

  /* HintMode */
  JS_SET_GL_CONSTANT(proto, DONT_CARE);
  JS_SET_GL_CONSTANT(proto, FASTEST);
  JS_SET_GL_CONSTANT(proto, NICEST);

  /* HintTarget */
  JS_SET_GL_CONSTANT(proto, GENERATE_MIPMAP_HINT);

  /* DataType */
  JS_SET_GL_CONSTANT(proto, BYTE);
  JS_SET_GL_CONSTANT(proto, UNSIGNED_BYTE);
  JS_SET_GL_CONSTANT(proto, SHORT);
  JS_SET_GL_CONSTANT(proto, UNSIGNED_SHORT);
  JS_SET_GL_CONSTANT(proto, INT);
  JS_SET_GL_CONSTANT(proto, UNSIGNED_INT);
  JS_SET_GL_CONSTANT(proto, FLOAT);
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, FIXED);
#endif

  /* PixelFormat */
  JS_SET_GL_CONSTANT(proto, DEPTH_COMPONENT);
  JS_SET_GL_CONSTANT(proto, ALPHA);
  JS_SET_GL_CONSTANT(proto, RGB);
  JS_SET_GL_CONSTANT(proto, RGBA);
  JS_SET_GL_CONSTANT(proto, LUMINANCE);
  JS_SET_GL_CONSTANT(proto, LUMINANCE_ALPHA);

  /* PixelType */
  /*      GL_UNSIGNED_BYTE */
  JS_SET_GL_CONSTANT(proto, UNSIGNED_SHORT_4_4_4_4);
  JS_SET_GL_CONSTANT(proto, UNSIGNED_SHORT_5_5_5_1);
  JS_SET_GL_CONSTANT(proto, UNSIGNED_SHORT_5_6_5);

  /* Shaders */
  JS_SET_GL_CONSTANT(proto, FRAGMENT_SHADER);
  JS_SET_GL_CONSTANT(proto, VERTEX_SHADER);
  JS_SET_GL_CONSTANT(proto, MAX_VERTEX_ATTRIBS);
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, MAX_VERTEX_UNIFORM_VECTORS);
  JS_SET_GL_CONSTANT(proto, MAX_VARYING_VECTORS);
#endif
  JS_SET_GL_CONSTANT(proto, MAX_COMBINED_TEXTURE_IMAGE_UNITS);
  JS_SET_GL_CONSTANT(proto, MAX_VERTEX_TEXTURE_IMAGE_UNITS);
  JS_SET_GL_CONSTANT(proto, MAX_TEXTURE_IMAGE_UNITS);
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, MAX_FRAGMENT_UNIFORM_VECTORS);
#endif
  JS_SET_GL_CONSTANT(proto, SHADER_TYPE);
  JS_SET_GL_CONSTANT(proto, DELETE_STATUS);
  JS_SET_GL_CONSTANT(proto, LINK_STATUS);
  JS_SET_GL_CONSTANT(proto, VALIDATE_STATUS);
  JS_SET_GL_CONSTANT(proto, ATTACHED_SHADERS);
  JS_SET_GL_CONSTANT(proto, ACTIVE_UNIFORMS);
  JS_SET_GL_CONSTANT(proto, ACTIVE_UNIFORM_MAX_LENGTH);
  JS_SET_GL_CONSTANT(proto, ACTIVE_ATTRIBUTES);
  JS_SET_GL_CONSTANT(proto, ACTIVE_ATTRIBUTE_MAX_LENGTH);
  JS_SET_GL_CONSTANT(proto, SHADING_LANGUAGE_VERSION);
  JS_SET_GL_CONSTANT(proto, CURRENT_PROGRAM);

  /* StencilFunction */
  JS_SET_GL_CONSTANT(proto, NEVER);
  JS_SET_GL_CONSTANT(proto, LESS);
  JS_SET_GL_CONSTANT(proto, EQUAL);
  JS_SET_GL_CONSTANT(proto, LEQUAL);
  JS_SET_GL_CONSTANT(proto, GREATER);
  JS_SET_GL_CONSTANT(proto, NOTEQUAL);
  JS_SET_GL_CONSTANT(proto, GEQUAL);
  JS_SET_GL_CONSTANT(proto, ALWAYS);

  /* StencilOp */
  /*      GL_ZERO */
  JS_SET_GL_CONSTANT(proto, KEEP);
  JS_SET_GL_CONSTANT(proto, REPLACE);
  JS_SET_GL_CONSTANT(proto, INCR);
  JS_SET_GL_CONSTANT(proto, DECR);
  JS_SET_GL_CONSTANT(proto, INVERT);
  JS_SET_GL_CONSTANT(proto, INCR_WRAP);
  JS_SET_GL_CONSTANT(proto, DECR_WRAP);

  /* StringName */
  JS_SET_GL_CONSTANT(proto, VENDOR);
  JS_SET_GL_CONSTANT(proto, RENDERER);
  JS_SET_GL_CONSTANT(proto, VERSION);
  JS_SET_GL_CONSTANT(proto, EXTENSIONS);

  /* TextureMagFilter */
  JS_SET_GL_CONSTANT(proto, NEAREST);
  JS_SET_GL_CONSTANT(proto, LINEAR);

  /* TextureMinFilter */
  /*      GL_NEAREST */
  /*      GL_LINEAR */
  JS_SET_GL_CONSTANT(proto, NEAREST_MIPMAP_NEAREST);
  JS_SET_GL_CONSTANT(proto, LINEAR_MIPMAP_NEAREST);
  JS_SET_GL_CONSTANT(proto, NEAREST_MIPMAP_LINEAR);
  JS_SET_GL_CONSTANT(proto, LINEAR_MIPMAP_LINEAR);

  /* TextureParameterName */
  JS_SET_GL_CONSTANT(proto, TEXTURE_MAG_FILTER);
  JS_SET_GL_CONSTANT(proto, TEXTURE_MIN_FILTER);
  JS_SET_GL_CONSTANT(proto, TEXTURE_WRAP_S);
  JS_SET_GL_CONSTANT(proto, TEXTURE_WRAP_T);

  /* TextureTarget */
  /*      GL_TEXTURE_2D */
  JS_SET_GL_CONSTANT(proto, TEXTURE);

  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP);
  JS_SET_GL_CONSTANT(proto, TEXTURE_BINDING_CUBE_MAP);
  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP_POSITIVE_X);
  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP_NEGATIVE_X);
  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP_POSITIVE_Y);
  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP_NEGATIVE_Y);
  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP_POSITIVE_Z);
  JS_SET_GL_CONSTANT(proto, TEXTURE_CUBE_MAP_NEGATIVE_Z);
  JS_SET_GL_CONSTANT(proto, MAX_CUBE_MAP_TEXTURE_SIZE);

  /* TextureUnit */
  JS_SET_GL_CONSTANT(proto, TEXTURE0);
  JS_SET_GL_CONSTANT(proto, TEXTURE1);
  JS_SET_GL_CONSTANT(proto, TEXTURE2);
  JS_SET_GL_CONSTANT(proto, TEXTURE3);
  JS_SET_GL_CONSTANT(proto, TEXTURE4);
  JS_SET_GL_CONSTANT(proto, TEXTURE5);
  JS_SET_GL_CONSTANT(proto, TEXTURE6);
  JS_SET_GL_CONSTANT(proto, TEXTURE7);
  JS_SET_GL_CONSTANT(proto, TEXTURE8);
  JS_SET_GL_CONSTANT(proto, TEXTURE9);
  JS_SET_GL_CONSTANT(proto, TEXTURE10);
  JS_SET_GL_CONSTANT(proto, TEXTURE11);
  JS_SET_GL_CONSTANT(proto, TEXTURE12);
  JS_SET_GL_CONSTANT(proto, TEXTURE13);
  JS_SET_GL_CONSTANT(proto, TEXTURE14);
  JS_SET_GL_CONSTANT(proto, TEXTURE15);
  JS_SET_GL_CONSTANT(proto, TEXTURE16);
  JS_SET_GL_CONSTANT(proto, TEXTURE17);
  JS_SET_GL_CONSTANT(proto, TEXTURE18);
  JS_SET_GL_CONSTANT(proto, TEXTURE19);
  JS_SET_GL_CONSTANT(proto, TEXTURE20);
  JS_SET_GL_CONSTANT(proto, TEXTURE21);
  JS_SET_GL_CONSTANT(proto, TEXTURE22);
  JS_SET_GL_CONSTANT(proto, TEXTURE23);
  JS_SET_GL_CONSTANT(proto, TEXTURE24);
  JS_SET_GL_CONSTANT(proto, TEXTURE25);
  JS_SET_GL_CONSTANT(proto, TEXTURE26);
  JS_SET_GL_CONSTANT(proto, TEXTURE27);
  JS_SET_GL_CONSTANT(proto, TEXTURE28);
  JS_SET_GL_CONSTANT(proto, TEXTURE29);
  JS_SET_GL_CONSTANT(proto, TEXTURE30);
  JS_SET_GL_CONSTANT(proto, TEXTURE31);
  JS_SET_GL_CONSTANT(proto, ACTIVE_TEXTURE);

  /* TextureWrapMode */
  JS_SET_GL_CONSTANT(proto, REPEAT);
  JS_SET_GL_CONSTANT(proto, CLAMP_TO_EDGE);
  JS_SET_GL_CONSTANT(proto, MIRRORED_REPEAT);

  /* Uniform Types */
  JS_SET_GL_CONSTANT(proto, FLOAT_VEC2);
  JS_SET_GL_CONSTANT(proto, FLOAT_VEC3);
  JS_SET_GL_CONSTANT(proto, FLOAT_VEC4);
  JS_SET_GL_CONSTANT(proto, INT_VEC2);
  JS_SET_GL_CONSTANT(proto, INT_VEC3);
  JS_SET_GL_CONSTANT(proto, INT_VEC4);
  JS_SET_GL_CONSTANT(proto, BOOL);
  JS_SET_GL_CONSTANT(proto, BOOL_VEC2);
  JS_SET_GL_CONSTANT(proto, BOOL_VEC3);
  JS_SET_GL_CONSTANT(proto, BOOL_VEC4);
  JS_SET_GL_CONSTANT(proto, FLOAT_MAT2);
  JS_SET_GL_CONSTANT(proto, FLOAT_MAT3);
  JS_SET_GL_CONSTANT(proto, FLOAT_MAT4);
  JS_SET_GL_CONSTANT(proto, SAMPLER_2D);
  JS_SET_GL_CONSTANT(proto, SAMPLER_CUBE);

  /* Vertex Arrays */
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_ENABLED);
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_SIZE);
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_STRIDE);
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_TYPE);
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_NORMALIZED);
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_POINTER);
  JS_SET_GL_CONSTANT(proto, VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);

  /* Read Format */
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, IMPLEMENTATION_COLOR_READ_TYPE);
  JS_SET_GL_CONSTANT(proto, IMPLEMENTATION_COLOR_READ_FORMAT);
#endif

  /* Shader Source */
  JS_SET_GL_CONSTANT(proto, COMPILE_STATUS);
  JS_SET_GL_CONSTANT(proto, INFO_LOG_LENGTH);
  JS_SET_GL_CONSTANT(proto, SHADER_SOURCE_LENGTH);
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, SHADER_COMPILER);
#endif

  /* Shader Binary */
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, SHADER_BINARY_FORMATS);
  JS_SET_GL_CONSTANT(proto, NUM_SHADER_BINARY_FORMATS);
#endif

  /* Shader Precision-Specified Types */
#ifndef __APPLE__
  JS_SET_GL_CONSTANT(proto, LOW_FLOAT);
  JS_SET_GL_CONSTANT(proto, MEDIUM_FLOAT);
  JS_SET_GL_CONSTANT(proto, HIGH_FLOAT);
  JS_SET_GL_CONSTANT(proto, LOW_INT);
  JS_SET_GL_CONSTANT(proto, MEDIUM_INT);
  JS_SET_GL_CONSTANT(proto, HIGH_INT);
#endif

  /* Framebuffer Object. */
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER);

  JS_SET_GL_CONSTANT(proto, RGBA4);
  JS_SET_GL_CONSTANT(proto, RGB5_A1);
#ifndef __APPLE__
  //JS_SET_GL_CONSTANT(proto, RGB565);
#endif
  JS_SET_GL_CONSTANT(proto, DEPTH_COMPONENT16);
  JS_SET_GL_CONSTANT(proto, STENCIL_INDEX);
  JS_SET_GL_CONSTANT(proto, STENCIL_INDEX8);

  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_WIDTH);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_HEIGHT);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_INTERNAL_FORMAT);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_RED_SIZE);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_GREEN_SIZE);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_BLUE_SIZE);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_ALPHA_SIZE);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_DEPTH_SIZE);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_STENCIL_SIZE);

  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);

  JS_SET_GL_CONSTANT(proto, COLOR_ATTACHMENT0);
  JS_SET_GL_CONSTANT(proto, DEPTH_ATTACHMENT);
  JS_SET_GL_CONSTANT(proto, STENCIL_ATTACHMENT);

  JS_SET_GL_CONSTANT(proto, NONE);

  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_COMPLETE);
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
#ifndef __APPLE__
  //JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_INCOMPLETE_DIMENSIONS);
#endif
  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_UNSUPPORTED);

  JS_SET_GL_CONSTANT(proto, FRAMEBUFFER_BINDING);
  JS_SET_GL_CONSTANT(proto, RENDERBUFFER_BINDING);
  JS_SET_GL_CONSTANT(proto, MAX_RENDERBUFFER_SIZE);

  JS_SET_GL_CONSTANT(proto, INVALID_FRAMEBUFFER_OPERATION);

  // WebGL-specific enums
  JS_SET_NUM_CONSTANT(proto, "UNPACK_FLIP_Y_WEBGL", 0x9240);
  JS_SET_NUM_CONSTANT(proto, "UNPACK_PREMULTIPLY_ALPHA_WEBGL", 0x9241);
  JS_SET_NUM_CONSTANT(proto, "CONTEXT_LOST_WEBGL", 0x9242);
  JS_SET_NUM_CONSTANT(proto, "UNPACK_COLORSPACE_CONVERSION_WEBGL", 0x9243);
  JS_SET_NUM_CONSTANT(proto, "BROWSER_DEFAULT_WEBGL", 0x9244);

  // Export function
  target->Set(NanNew<String>("WebGLRenderingContext"), tpl->GetFunction());
}

} // end namespace HeadlessGL

NODE_MODULE(webgl, HeadlessGL::Init)
