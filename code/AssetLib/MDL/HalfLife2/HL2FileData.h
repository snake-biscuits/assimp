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

/** @file  HL1FileData.h
 *  @brief Definition of in-memory structures for the
 *         Half-Life 2 version 48 (2013 Source SDK) MDL file format.
 */

#ifndef AI_HL2FILEDATA_INCLUDED
#define AI_HL2FILEDATA_INCLUDED

#include "HalfLifeMDLBaseHeader.h"

#include <assimp/Compiler/pushpack1.h>
#include <assimp/types.h>

namespace Assimp {
namespace MDL {
namespace HalfLife {

using vec3_t = float[3];
using vec4_t = float[4];
using mat3x4_t = float[3][4];

/** \struct Header_HL2_v48
 *  \brief Data structure for the HL2 version 48 (2013 Source SDK) MDL file header.
 */
struct Header_HL2_v48 : HalfLifeMDLBaseHeader {  // studiohdr_t
    // https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/studio.h#L2050
    int32_t checksum; // needs to match checksum in external .phy & .vtx files
    char name[64];
    int32_t file_size;
    vec3_t eye_position; // ideal eye position
    vec3_t light_position; // point to calculate lighting from
    vec3_t hull_min; // ideal movement hull size
    vec3_t hull_max;
    vec3_t view_bbmin; // clipping bounding box
    vec3_t view_bbmax;
    int32_t flags;
    // counts & indices to start of array in .mdl file
    int32_t num_bones, bone_index; // Bone_HL2_v48
    int32_t num_bone_controllers, bone_controller_index; // BoneController_HL2_v48
    int32_t num_hitbox_sets, hitbox_set_index; // HitBox_HL2_v48
    int32_t num_local_animations, local_animation_index; // Animation_HL2_v48
    int32_t num_local_sequences, local_sequence_index; // Sequence_HL2_v48
    int32_t activity_list_version, events_indexed; // private, tied to sequences
    int32_t num_textures, texture_index; // Texture_HL2_v48
    int32_t num_texture_dirs, texture_dir_index;
    int32_t num_skin_ref, num_skin_families, skin_index;
    int32_t num_bodyparts, bodypart_index;
    int32_t num_local_attachments, local_attachment_index; // Attachment_HL2_v48
    int32_t num_local_nodes, local_node_index, local_node_name_index;
    int32_t num_flexes, flex_index;
    int32_t num_flex_controllers, flex_controller_index;
    int32_t num_flex_rules, flex_rule_index;
    int32_t num_ik_chains, ik_chain_index;
    int32_t num_mouths, mouth_index;
    int32_t num_local_pose_parameters, local_pose_parameter_index;
    int32_t surfaceprop_index; // zero-terminated string
    int32_t keyvalue_index, keyvalue_size;
    int32_t num_local_ik_autoplay_locks, local_ik_autoplay_lock_index;
    float mass;
    int32_t contents;
    int32_t num_include_models, include_model_index; // Model_HL2_v48
    int32_t virtual_model;
    int32_t animation_block_name_index; // zero-terminated string
    int32_t num_animation_blocks, animation_block_index;
    int32_t animation_block_model; // mutable void pointer
    int32_t bonetable_by_name_index;
    int32_t pVertexBase, pIndexBase; // cached with virtual model
    int8_t const_directional_light_dot; // if (flags & AI_MDL_HL2_STUDIOHDR_FLAGS_CONSTANT_DIRECTIONAL_LIGHT_DOT)
    int8_t root_lod, num_allowed_root_lods;
    int8_t unused_1;
    int32_t unused_2;
    int32_t num_flex_controller_uis, flex_controller_ui_index;
    float vertex_animation_fixed_point_scale; // if (flags & AI_MDL_HL2_STUDIOHDR_FLAGS_VERT_ANIM_FIXED_POINT_SCALE)
    int32_t surfaceprop_lookup; // this index must be cached by the loader, not saved in the file
    int32_t studiohdr2_index; // Header2_HL2_v48
    int32_t unused_3;
} PACK_STRUCT;

/** \struct Header2_HL2_v48
 *  \brief Data structure for the HL2 version 48 (2013 Source SDK) MDL file header2.
 */
struct Header2_HL2_v48 { // studiohdr2_t
    int32_t num_source_bone_transform, source_bone_transform_index;
    int32_t illum_position_attachment_index;
    float max_eye_deflection; // defaults to cos(30) if 0.0f
    int32_t linear_bone_index;
    int32_t name_index;
    int32_t bone_flex_driver_count, bone_flex_driver_index;
    int32_t reserved[56]; // Source SDK doesn't immediately state why this is reserved
} PACK_STRUCT;

/** \struct Model_HL2_v48
 *  \brief Data structure for a model in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Model_HL2_v48 {  // mstudiomodel_t
    char name[64];
    int32_t type; // TODO: enum?
    float bounding_radius;
    int32_t num_meshes, mesh_index;
    int32_t num_vertices, vertex_index; // vertex Vector
    int32_t tangents_index; // tangents Vector
    int32_t num_attachments, attachment_index;
    int32_t num_eyeballs, eyeball_index;
    int32_t vertex_data_pointer, tangent_data_pointer; // mstudio_modelvertexdata_t object
    int32_t unused[8]; // remove as appropriate
} PACK_STRUCT;

/** \struct Mesh_HL2_v48
 *  \brief Data structure for a mesh in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Mesh_HL2_v48 {  // mstudiomesh_t
    int32_t material;
    int32_t model_index;
    int32_t num_vertices, vertex_offset; // vertex mstudiovertex_t
    int32_t num_flexes, flex_index; // vertex animation
    int32_t material_type, material_param; // enums?
    int32_t mesh_id; // a unique ordinal for this mesh
    vec3_t center;
    int32_t vertex_data_pointer, tangent_data_pointer; // mstudio_modelvertexdata_t object
    int32_t unused[8]; // remove as appropriate
} PACK_STRUCT;

/** \struct Texture_HL2_v48
 *  \brief Data structure for a texture in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Texture_HL2_v48 {  // mstudiotexture_t
    // NOTE: v52's name_index is actually the offset of the Texture + name_index (or client_material_pointer)
    // -- unsure how .vmt names are indexed
    int32_t name_index; // points at texture dir? where do we get the material filename?
    int32_t flags;
    int32_t used; // not a simple 0 or 1?
    int32_t material_pointer;
    int32_t client_material_pointer;
    int32_t unused[11];
} PACK_STRUCT;

/** \struct Bone_HL2_v48
 *  \brief Data structure for a bone in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Bone_HL2_v48 {  // mstudiobone_t
    int32_t name_index;
    int32_t parent; // parent bone
    int32_t bone_controller_indices[6]; // -1 == none
    // default values
    vec3_t position;
    vec4_t quaternion;
    vec3_t rotation; // Euler angles in radians
    // compression scale
    vec3_t position_scale;
    vec3_t rotation_scale;
    mat3x4_t pose_to_bone;
    vec4_t alignment;
    int32_t flags;
    int32_t procedural_rule_type;
    int32_t procedural_rule_index;
    int32_t physics_bone;
    int32_t surfaceprop_index; // index into string table
    int32_t contents; // BSPFlags.h contents flags
    int32_t unused[8]; // remove as appropriate
} PACK_STRUCT;

// TODO: BoneController_HL2_v48

// TODO: HitBox_HL2_v48

/** \struct Animation_HL2_v48
 *  \brief Data structure for an animation description in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Animation_HL2_v48 {  // mstudioanimdesc_t
    int32_t base_pointer;
    int32_t name_index; // zero-terminated string
    float framerate; // in frames-per-second
    int32_t flags; // looping / non-looping etc.
    int32_t num_frames;
    // piecewise movement
    int32_t num_movements, movement_index;
    int32_t unused[6]; // remove as appropriate (and zero if loading older versions)
    int32_t animation_block, animation_index; // non-zero when anim data isn't in sections
    // Inverse Kinematics
    int32_t num_ik_rules, ik_rule_index; // non-zero when IK data is stored in the mdl
    int32_t animation_block_ik_rule_index; // non-zero when IK data is stored in animation_block file
    int32_t num_local_hierarchy, local_hierarchy_index;
    int32_t section_index, section_frames; // number of frames used in each fast lookup section, zero if not used
    int16_t zero_frame_span, zero_frame_count; // frames per span & number of spans
    int32_t zero_frame_index;
    float zero_frame_stall_time; // saved during read stalls
} PACK_STRUCT;

/** \struct Sequence_HL2_v48
 *  \brief Data structure for a sequence description in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Sequence_HL2_v48 { // mstudioseqdesc_t
    int32_t base_pointer;
    int32_t label_index; // zero-terminated string
    int32_t activity_name_index;
    int32_t flags; // looping / non-looping etc.
    int32_t activity; // initialized at loadtime to game DLL values
    int32_t act_weight;
    int32_t num_events, event_index;
    vec3_t bb_mins, bb_maxs; // per-sequence bounds
    int32_t num_blends;
    int32_t anim_index_index; // index into array of shorts; group_size[0] x group_size[1] in length
    int32_t movement_index; // [blend] float array for blended movement
    int32_t group_size[2]; // X-by-Y table of animations
    int32_t param_index[2]; // X, Y, Z, XR, YR, ZR
    float param_start[2]; // local (0..1) starting value
    float param_end[2]; // local (0..1) ending value
    int32_t param_parent;
    float fade_in_time, fade_out_time; // ideal cross fade times (0.2 default)
    int32_t local_entry_node, local_exit_node; // transition nodes
    int32_t node_flags; // transition rules
    float entry_phase, exit_phase; // used to match gait
    float last_frame; // frame that should generate "EndOfSequence"
    int32_t next_seq; // auto advancing sequences
    int32_t pose; // index of delta animation between end and nextseq
    int32_t num_ik_rules;
    int32_t num_auto_layers, auto_layer_index;
    int32_t weight_list_index;
    int32_t pose_key_index;
    int32_t num_ik_locks, ik_lock_index;
    int32_t keyvalue_index, keyvalue_size;
    int32_t cycle_pose_index; // index of pose parameter to use as cycle index
    int32_t unused[7]; // remove/add as appropriate (grow back to 8 ints on version change!)
} PACK_STRUCT;

/** \struct Attachment_HL2_v48
 *  \brief Data structure for an attachment in HL2 version 48 (2013 Source SDK) MDL files.
 */
struct Attachment_HL2_v48 {  // mstudioattachment_t
    int32_t name_index; // zero-terminated string
    uint32_t flags;
    int32_t local_bone;
    mat3x4_t local_matrix; // attachment point
    int32_t unused[8];
} PACK_STRUCT;

#if (!defined AI_MDL_HL2_MIN_VERSION)
#define AI_MDL_HL2_MIN_VERSION 48
#endif
#if (!defined AI_MDL_HL2_MAX_VERSION)
#define AI_MDL_HL2_MAX_VERSION 52
#endif
#if (!defined AI_MDL_HL2_MAX_TRIANGLES)
#define AI_MDL_HL2_MAX_TRIANGLES 65536
#endif
#if (!defined AI_MDL_HL2_MAX_VERTICES)
#define AI_MDL_HL2_MAX_VERTICES 65536
#endif
#if (!defined AI_MDL_HL2_MAX_FLEX_VERTICES)
#define AI_MDL_HL2_MAX_FLEX_VERTICES 10000
#endif
#if (!defined AI_MDL_HL2_MAX_SKINS)
#define AI_MDL_HL2_MAX_SKINS 32
#endif
#if (!defined AI_MDL_HL2_V48_MAX_BONES)
#define AI_MDL_HL2_V48_MAX_BONES 128
#endif
#if (!defined AI_MDL_HL2_V52_MAX_BONES)
#define AI_MDL_HL2_V52_MAX_BONES 256
#endif
#if (!defined AI_MDL_HL2_MAX_BONE_CONTROLLERS)
#define AI_MDL_HL2_MAX_BONE_CONTROLLERS 4
#endif
#if (!defined AI_MDL_HL2_MAX_BONE_BITS)
#define AI_MDL_HL2_MAX_BONE_BITS 7
#endif
#if (!defined AI_MDL_HL2_MAX_BONES_PER_VERTEX)
#define AI_MDL_HL2_MAX_BONES_PER_VERTEX 3
#endif
#if (!defined AI_MDL_HL2_MAX_FLEXES)
#define AI_MDL_HL2_MAX_FLEXES 1024
#endif
#if (!defined AI_MDL_HL2_MAX_FLEX_CONTROLLERS)
#define AI_MDL_HL2_MAX_FLEX_CONTROLLERS 96
#endif
#if (!defined AI_MDL_HL2_MAX_POSE_PARAMATERS)
#define AI_MDL_HL2_MAX_POSE_PARAMATERS 24
#endif
#if (!defined AI_MDL_HL2_ANIMATION_BLOCKS)
#define AI_MDL_HL2_ANIMATION_BLOCKS 256
#endif
// VVD
#if (!defined AI_MDL_HL2_VVD_VERSION)
#define AI_MDL_HL2_VVD_VERSION 4
#endif
#if (!defined AI_MDL_HL2_LODS)
#define AI_MDL_HL2_LODS 8
#endif

// STUDIOHDR FLAGS
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_AUTOGENERATED_HITBOX)
// This flag is set if no hitbox information was specified
#define AI_MDL_HL2_STUDIOHDR_FLAGS_AUTOGENERATED_HITBOX (1 << 0)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_USES_ENV_CUBEMAP)
// This flag is set at loadtime, not mdl build time so that we don't have to rebuild
// models when we change materials.
#define AI_MDL_HL2_STUDIOHDR_FLAGS_USES_ENV_CUBEMAP (1 << 1)
#endif
#if (!defined STUDIOHDR_FLAGS_FORCE_OPAQUE)
// Use this when there are translucent parts to the model but we're not going to sort it
#define AI_MDL_HL2_STUDIOHDR_FLAGS_FORCE_OPAQUE (1 << 2)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_TRANSLUCENT_TWOPASS)
// Use this when we want to render the opaque parts during the opaque pass
// and the translucent parts during the translucent pass
#define AI_MDL_HL2_STUDIOHDR_FLAGS_TRANSLUCENT_TWOPASS (1 << 3)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_STATIC_PROP)
// This is set any time the .qc files has $staticprop in it
// Means there's no bones and no transforms
#define AI_MDL_HL2_STUDIOHDR_FLAGS_STATIC_PROP (1 << 4)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_USES_FB_TEXTURE)
// This flag is set at loadtime, not mdl build time so that we don't have to rebuild
// models when we change materials.
#define AI_MDL_HL2_STUDIOHDR_FLAGS_USES_FB_TEXTURE (1 << 5)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_HASSHADOWLOD)
// This flag is set by studiomdl.exe if a separate "$shadowlod" entry was present
// for the .mdl (the shadow lod is the last entry in the lod list if present)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_HASSHADOWLOD (1 << 6)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_USES_BUMPMAPPING)
// This flag is set at loadtime, not mdl build time so that we don't have to rebuild
// models when we change materials.
#define AI_MDL_HL2_STUDIOHDR_FLAGS_USES_BUMPMAPPING (1 << 7)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_USE_SHADOWLOD_MATERIALS)
// This flag is set when we should use the actual materials on the shadow LOD
// instead of overriding them with the default one (necessary for translucent shadows)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_USE_SHADOWLOD_MATERIALS (1 << 8)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_OBSOLETE)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_OBSOLETE (1 << 9)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_UNUSED)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_UNUSED (1 << 10)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_NO_FORCED_FADE)
// This flag is set at mdl build time
#define AI_MDL_HL2_STUDIOHDR_FLAGS_NO_FORCED_FADE (1 << 11)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_FORCE_PHONEME_CROSSFADE)
// The npc will lengthen the viseme check to always include two phonemes
#define AI_MDL_HL2_STUDIOHDR_FLAGS_FORCE_PHONEME_CROSSFADE (1 << 12)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_CONSTANT_DIRECTIONAL_LIGHT_DOT)
// This flag is set when the .qc has $constantdirectionallight in it
// If set, we use constantdirectionallightdot to calculate light intensity
// rather than the normal directional dot product
// only valid if AI_MDL_HL2_STUDIOHDR_FLAGS_STATIC_PROP is also set
#define AI_MDL_HL2_STUDIOHDR_FLAGS_CONSTANT_DIRECTIONAL_LIGHT_DOT (1 << 13)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_FLEXES_CONVERTED)
// Flag to mark delta flexes as already converted from disk format to memory format
#define AI_MDL_HL2_STUDIOHDR_FLAGS_FLEXES_CONVERTED (1 << 14)
#endif
#if (!defined AI_MDL_HL2_AI_MDL_HL2_STUDIOHDR_FLAGS_BUILT_IN_PREVIEW_MODE)
// Indicates the studiomdl was built in preview mode
#define AI_MDL_HL2_AI_MDL_HL2_STUDIOHDR_FLAGS_BUILT_IN_PREVIEW_MODE (1 << 15)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_AMBIENT_BOOST)
// Ambient boost (runtime flag)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_AMBIENT_BOOST (1 << 16)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_DO_NOT_CAST_SHADOWS)
// Don't cast shadows from this model (useful on first-person models)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_DO_NOT_CAST_SHADOWS (1 << 17)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_CAST_TEXTURE_SHADOWS)
// Alpha textures should cast shadows in vrad on this model (ONLY prop_static!)
#define AI_MDL_HL2_STUDIOHDR_FLAGS_CAST_TEXTURE_SHADOWS (1 << 18)
#endif
#if (!defined AI_MDL_HL2_STUDIOHDR_FLAGS_VERT_ANIM_FIXED_POINT_SCALE)
// Flagged on load to indicate no animation events on this model
#define AI_MDL_HL2_STUDIOHDR_FLAGS_VERT_ANIM_FIXED_POINT_SCALE (1 << 21)
#endif

} // namespace HalfLife
} // namespace MDL
} // namespace Assimp

#endif // AI_HL2FILEDATA_INCLUDED
