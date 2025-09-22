/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2022, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file  HL2VVCFileData.h
 *  @brief Definition of external .vvc structures for the
 *         Half-Life 2 version 48 (2013 Source SDK) MDL file format.
 */

// NOTE: .vvc files are mostly the same as .vvd files, but have compressed vertex data

#ifndef AI_HL2VVCFILEDATA_INCLUDED
#define AI_HL2VVCFILEDATA_INCLUDED

#include "HalfLifeMDLBaseHeader.h"

#include <assimp/Compiler/pushpack1.h>
#include <assimp/types.h>

namespace Assimp {
namespace MDL {
namespace HalfLife {
namespace VVC {

using vec3_t = float[3];

#define AI_MDL_MAGIC_NUMBER_BE_HL2_VVC AI_MAKE_MAGIC("IDCV")
#define AI_MDL_MAGIC_NUMBER_LE_HL2_VVC AI_MAKE_MAGIC("VCDI")

struct ThinVertices { // thinModelVertices_t
    // https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/studio.h#L1728
    int32_t num_bone_influences; // Number of bone influences per vertex, N
    float *bone_weights; // This array stores (N-1) weights per vertex (unless N is zero)
    int8_t *bone_indices; // This array stores N indices per vertex
    vec3_t *positions;
    uint16_t *normals; // Normals are compressed into 16 bits apiece (see PackNormal_UBYTE4() )
} thinModelVertices_t;

} // namespace VVC
} // namespace HalfLife
} // namespace MDL
} // namespace Assimp

#endif // AI_HL2VVCFILEDATA_INCLUDED
