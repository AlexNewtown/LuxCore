#include <string>
namespace luxrays { namespace ocl {
std::string KernelSource_frame_funcs = 
"#line 2 \"frame_funcs.cl\"\n"
"\n"
"/***************************************************************************\n"
" * Copyright 1998-2015 by authors (see AUTHORS.txt)                        *\n"
" *                                                                         *\n"
" *   This file is part of LuxRender.                                       *\n"
" *                                                                         *\n"
" * Licensed under the Apache License, Version 2.0 (the \"License\");         *\n"
" * you may not use this file except in compliance with the License.        *\n"
" * You may obtain a copy of the License at                                 *\n"
" *                                                                         *\n"
" *     http://www.apache.org/licenses/LICENSE-2.0                          *\n"
" *                                                                         *\n"
" * Unless required by applicable law or agreed to in writing, software     *\n"
" * distributed under the License is distributed on an \"AS IS\" BASIS,       *\n"
" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*\n"
" * See the License for the specific language governing permissions and     *\n"
" * limitations under the License.                                          *\n"
" ***************************************************************************/\n"
"\n"
"void Frame_SetFromZ(__global Frame *frame, const float3 Z) {\n"
"	float3 X, Y;\n"
"	CoordinateSystem(Z, &X, &Y);\n"
"\n"
"	VSTORE3F(X, &frame->X.x);\n"
"	VSTORE3F(Y, &frame->Y.x);\n"
"	VSTORE3F(Z, &frame->Z.x);\n"
"}\n"
"\n"
"float3 ToWorld(const float3 X, const float3 Y, const float3 Z, const float3 v) {\n"
"	return X * v.x + Y * v.y + Z * v.z;\n"
"}\n"
"\n"
"float3 Frame_ToWorld(__global Frame *frame, const float3 v) {\n"
"	return ToWorld(VLOAD3F(&frame->X.x), VLOAD3F(&frame->Y.x), VLOAD3F(&frame->Z.x), v);\n"
"}\n"
"\n"
"float3 ToLocal(const float3 X, const float3 Y, const float3 Z, const float3 a) {\n"
"	return (float3)(dot(a, X), dot(a, Y), dot(a, Z));\n"
"}\n"
"\n"
"float3 Frame_ToLocal(__global Frame *frame, const float3 v) {\n"
"	return ToLocal(VLOAD3F(&frame->X.x), VLOAD3F(&frame->Y.x), VLOAD3F(&frame->Z.x), v);\n"
"}\n"
; } }
