#define PLUG_MFR "MatthieuBrucher"
#define PLUG_NAME "ATKSideChainCompressor"

#define PLUG_CLASS_NAME ATKSideChainCompressor

#define BUNDLE_MFR "MatthieuBrucher"
#define BUNDLE_NAME "ATKSideChainCompressor"

#define PLUG_ENTRY ATKSideChainCompressor_Entry
#define PLUG_VIEW_ENTRY ATKSideChainCompressor_ViewEntry

#define PLUG_ENTRY_STR "ATKSideChainCompressor_Entry"
#define PLUG_VIEW_ENTRY_STR "ATKSideChainCompressor_ViewEntry"

#define VIEW_CLASS ATKSideChainCompressor_View
#define VIEW_CLASS_STR "ATKSideChainCompressor_View"

// Format        0xMAJR.MN.BG - in HEX! so version 10.1.5 would be 0x000A0105
#define PLUG_VER 0x00010000
#define VST3_VER_STR "1.0.0"

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'e1or'
// make sure this is not the same as BUNDLE_MFR
#define PLUG_MFR_ID 'MatB'

// ProTools stuff

#if (defined(AAX_API) || defined(RTAS_API)) && !defined(_PIDS_)
  #define _PIDS_
  const int PLUG_TYPE_IDS[2] = {'EFN1', 'EFN2'};
  const int PLUG_TYPE_IDS_AS[2] = {'EFA1', 'EFA2'}; // AudioSuite
#endif

#define PLUG_MFR_PT "MatthieuBrucher\nMatthieuBrucher\nMatthieuBrucher"
#define PLUG_NAME_PT "ATKSideChainCompressor\ne1or"
#define PLUG_TYPE_PT "Dynamics"
#define PLUG_DOES_AUDIOSUITE 1

/* PLUG_TYPE_PT can be "None", "EQ", "Dynamics", "PitchShift", "Reverb", "Delay", "Modulation", 
"Harmonic" "NoiseReduction" "Dither" "SoundField" "Effect" 
instrument determined by PLUG _IS _INST
*/

#define PLUG_CHANNEL_IO "2-2 4-2"

// Should be retrieved from ATK when the time comes
#define PLUG_LATENCY 0
#define PLUG_IS_INST 0

// if this is 0 RTAS can't get tempo info
#define PLUG_DOES_MIDI 0

#define PLUG_DOES_STATE_CHUNKS 0

// Unique IDs for each image resource.
#define STEREO_COMPRESSOR_ID 101
#define KNOB_ID 102
#define KNOB1_ID 103
#define SWITCH_ID 104

// Image resource locations for this plug.
#define STEREO_COMPRESSOR_FN "resources/img/metal.png"
#define KNOB_FN "resources/img/uni-small.png"
#define KNOB1_FN "resources/img/bi-small.png"
#define SWITCH_FN "resources/img/switch2-small.png"

// GUI default dimensions
#define GUI_WIDTH 1261
#define GUI_HEIGHT 280

// on MSVC, you must define SA_API in the resource editor preprocessor macros as well as the c++ ones
#if defined(SA_API) && !defined(OS_IOS)
#include "app_wrapper/app_resource.h"
#endif

// vst3 stuff
#define MFR_URL "matt.eifelle.com"
#define MFR_EMAIL "spam@me.com"
#define EFFECT_TYPE_VST3 "Fx|Dynamics"

/* "Fx|Analyzer"", "Fx|Delay", "Fx|Distortion", "Fx|Dynamics", "Fx|EQ", "Fx|Filter",
"Fx", "Fx|Instrument", "Fx|InstrumentExternal", "Fx|Spatial", "Fx|Generator",
"Fx|Mastering", "Fx|Modulation", "Fx|PitchShift", "Fx|Restoration", "Fx|Reverb",
"Fx|Surround", "Fx|Tools", "Instrument", "Instrument|Drum", "Instrument|Sampler",
"Instrument|Synth", "Instrument|Synth|Sampler", "Instrument|External", "Spatial",
"Spatial|Fx", "OnlyRT", "OnlyOfflineProcess", "Mono", "Stereo",
"Surround"
*/
