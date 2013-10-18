/*
  LVZ - An ugly C++ interface for writing LV2 plugins.
  Copyright 2008-2012 David Robillard <http://drobilla.net>

  This is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License,
  or (at your option) any later version.

  This software is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this software. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLUGIN_CLASS
#error "This file requires PLUGIN_CLASS to be defined"
#endif
#ifndef URI_PREFIX
#error "This file requires URI_PREFIX to be defined"
#endif
#ifndef PLUGIN_URI_SUFFIX
#error "This file requires PLUGIN_URI_SUFFIX to be defined"
#endif
#ifndef PLUGIN_HEADER
#error "This file requires PLUGIN_HEADER to be defined"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "audioeffectx.h"
#include "lv2.h"
#include "lv2/lv2plug.in/ns/ext/atom/atom.h"
#include "lv2/lv2plug.in/ns/ext/midi/midi.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include PLUGIN_HEADER


// Essa função trabalha como uma regra de 3 para adaptar os valores recebidos na instância do plugin
// (que encontram-se determinados no ttl)
// para valores de 0 a 1, pois o código do mda foi projetado para trabalhar com esses valores


float translateParameter(PLUGIN_CLASS* effect,int port,float value) {
    if(strcmp(effect->getUniqueID(), "mdaAmb") == 0) {
            switch(port) {
                case 0:
                return (value)/(10);
                case 1:
                return (value)/(100);
                case 2:
                return (value)/(100);
                case 3:
                return (value + 20)/(40);
            }
    }
    else if(strcmp(effect->getUniqueID(), "mdaBand") == 0) {
        switch(port) {
            case(0):
            return (value)/(3);
            case(1):
            return (value - 88)/(1020 - 88);
            case(2):
            return (value - 112)/(19606 - 112);
            case(3):
            return (value)/(60);
            case(4):
            return (value)/(60);
            case(5):
            return (value)/(60);
            case(6):
            return (value - 20)/(40);
            case(7):
            return (value - 20)/(40);
            case(8):
            return (value - 20)/(40);
            case(9):
            return (float) value;
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaBBox") == 0) {
        switch(port) {
            case(0):
            return (value + 40)/(40);
            case(1):
            return (value - 40)/(200);
            case(2):
            return (value + 80)/(92);
            case(3):
            return (value + 40)/(40);
            case(4):
            return (value - 22)/(3472);
            case(5):
            return (value + 80)/(92);
            case(6):
            return (value + 40)/(40);
            case(7):
            return (value - 22)/(3472);
            case(8):
            return (value + 80)/(92);
            case(9):
            return (value - 1)/(99);
            case(10):
            return (float) (value)/4;
            case(11):
            return (value + 41)/(41);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaCombo") == 0) {
        switch(port) {
            case(0):
            return  (float) (value)/6;
            case(1):
            return (value + 100)/(200);
            case(2):
            return (value + 100)/(200);
            case(3):
            return (value + 20)/(40);
            case(4):
            return  (float) value;
            case(5):
            return (value)/(100);
            case(6):
            return (value)/(100);
        }

    }
    else if(strcmp(effect->getUniqueID(), "mdaDeEss") == 0) {
        switch(port) {
            case(0):
            return (value + 60)/(60);
            case(1):
            return (value - 1000)/(11000);
            case(2):
            return (value + 20)/(40);
        }
    }
    //else if(strcmp(effect->getUniqueID(), "mdaDegrade") == 0) {

    //}
    //else if(strcmp(effect->getUniqueID(), "mdaDelay") == 0) {

    //}
    else if(strcmp(effect->getUniqueID(), "mdaDetune") == 0) {
        switch(port) {
            case(0):
            return (value)/(300);
            case(1):
            return (value)/(99);
            case(2):
            return (value + 20)/(40);
            case(3):
            return (value - 5.8)/(87.1);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaDither") == 0) {
        switch(port) {
            case(0):
            return (value - 8)/(16);
            case(1):
            return (value)/(3);
            case(2):
            return (value)/(4);
            case(3):
            return (value + 2)/(4);
            case(4):
            return 1 - pow(10.0, (value/40.0));
        }

    }
    else if(strcmp(effect->getUniqueID(), "mdaDubDelay") == 0) {
        switch(port) {
            case(0):
            return (value)/7341;
            case(1):
            return (value + 110)/(220);
            case(2):
            return (value + 100)/(200);
            case(3):
            return (value)/(100);
            case(4):
            return  1 - ((value - 0.10)/99.9);
            case(5):
            return (value)/(100);
            case(6):
            return (value + 34)/(40);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaDX10") == 0) {
        switch(port) {
            case(0):
            return (value)/(100);
            case(1):
            return (value)/(100);
            case(2):
            return (value)/(100);
            case(3):
            return (value)/(40);
            case(4):
            return (value)/(0.750);
            case(5):
            return (value)/(100);
            case(6):
            return (value)/(100);
            case(7):
            return (value)/(100);
            case(8):
            return (value)/(100);
            case(9):
            return (value)/(100);
            case(10):
            return (value)/(100);
            case(11):
            return (value + 3)/(6);
            case(12):
            return (value + 100)/(200);
            case(13):
            return (value)/(100);
            case(14):
            return (value)/(100);
            case(15):
            return (value)/(25);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaDynamics") == 0) {
        switch(port) {
            case(0):
            return (value + 40)/(40);
            case(1):
            return 1 - ((value + 17)/(17.5));
            case(2):
            return (value)/(40);
            case(3):
            return (value - 2)/(1569);
            case(4):
            return (value - 1)/(1570);
            case(5):
            return (value + 20)/(30);
            case(6):
            return (value + 60)/60;
            case(7):
            return (value - 5)/(15777);
            case(8):
            return (value - 9)/(17375);
            case(9):
            return (value)/(100);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaEPiano") == 0) {
        switch(port) {
            case(0):
            return (value)/(100);
            case(1):
            return (value)/(100);
            case(2):
            return (value + 50)/(100);
            case(3):
            return (value + 50)/(100);
            case(4):
            return (value + 100)/(200);
            case(5):
            return (value - 0.07)/(36.90);
            case(6):
            return (value)/(100);
            case(7):
            return (value)/(200);
            case(8):
            return (value);
            case(9):
            return (value + 50)/(100);
            case(10):
            return (value)/(50);
            case(11):
            return (value)/(100);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaImage") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value + 200)/(400);
            case(2):
            return (value + 100)/(200);
            case(3):
            return (value + 200)/(400);
            case(4):
            return (value + 100)/(200);
            case(5):
            return (value + 20)/(40);
        }
    }
    //else if(strcmp(effect->getUniqueID(), "mdaJX10") == 0) {

    //}
    else if(strcmp(effect->getUniqueID(), "mdaLeslie") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value)/(100);
            case(2):
            return (value)/(100);
            case(3):
            return (value)/(100);
            case(4):
            return (value)/(100);
            case(5):
            return (value)/(100);
            case(6):
            return (value - 150)/(1360);
            case(7):
            return (value + 20)/(40);
            case(8):
            return (value)/(200);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaLimiter") == 0) {
        switch(port) {
            case(0):
            return (value + 40)/(40);
            case(1):
            return (value + 20)/(40);
            case(2):
            return (value - 1)/(1570);
            case(3):
            return (value)/(1563);
            case(4):
            return (value);
        }
    }
    //else if(strcmp(effect->getUniqueID(), "mdaLoopLex") == 0) {

    //}
    //else if(strcmp(effect->getUniqueID(), "mdaLoudness") == 0) {

    //}
    else if(strcmp(effect->getUniqueID(), "mdaMultiBand") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value - 87)/(933);
            case(2):
            return (value - 111)/(19495);
            case(3):
            return (value)/(30);
            case(4):
            return (value)/(30);
            case(5):
            return (value)/(30);
            case(6):
            return (value + 20)/(40);
            case(7):
            return (value + 20)/(40);
            case(8):
            return (value + 20)/(40);
            case(9):
            return (value - 7)/(1748);
            case(10):
            return (value - 1)/(1570);
            case(11):
            return (value)/(200);
            case(12):
            return (value);
        }

    }
    else if(strcmp(effect->getUniqueID(), "mdaOverdrive") == 0) {
        switch(port) {
            case(0):
            return (value)/(100);
            case(1):
            return (value)/(100);
            case(2):
            return (value + 20)/(40);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaPiano") == 0) {
        switch(port) {
            case(0):
            return (value)/(100);
            case(1):
            return (value)/(100);
            case(2):
            return (value + 50)/(100);
            case(3):
            return (value)/(100);
            case(4):
            return (value)/(100);
            case(5):
            return (value)/(100);
            case(6):
            return (value)/(100);
            case(7):
            return (value)/(200);
            case(8):
            return (value);
            case(9):
            return (value + 50)/(100);
            case(10):
            return (value)/(50);
            case(11):
            return (value + 50)/(100);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaRePsycho") == 0) {
        switch(port) {
            case(0):
            return (value + 24)/(24);
            case(1):
            return (value + 99)/(99);
            case(2):
            return (value + 50)/(100);
            case(3):
            return (value + 30)/(30);
            case(4):
            return (value - 10)/(250);
            case(5):
            return (value)/(100);
            case(6):
            return (value);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaRezFilter") == 0) {
        switch(port) {
            case(0):
            return (value)/(100);
            case(1):
            return (value)/(100);
            case(2):
            return (value + 20)/(40);
            case(3):
            return (value + 100)/(200);
            case(4):
            return (value)/(160.83);
            case(5):
            return (value - 1.56)/(15510.08);
            case(6):
            return (value + 100)/(200);
            case(7):
            return (2 + log10(value))/4;
            case(8):
            return (value + 37)/(40);
            case(9):
            return (value)/(100);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaRingMod") == 0) {
         switch(port) {
            case(0):
            return (value)/(16000);
            case(1):
            return (value)/(100);
            case(2):
            return (value)/(100);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaRoundPan") == 0) {
        switch(port) {
            case(0):
            return (value + 180)/(360);
            case(1):
            return (value + 515)/(1030);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaShepard") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value + 100)/(200);
            case(2):
            return (value + 20)/(40);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaSplitter") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value - 100)/(9900);
            case(2):
            return (value);
            case(3):
            return (value + 40)/(40);
            case(4):
            return (value);
            case(5):
            return (value - 10)/(990);
            case(6):
            return (value + 20)/(40);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaStereo") == 0) {
        switch(port) {
            case(0):
            return (value + 100)/(200);
            case(1):
            return (value - 0.45)/(47.17);
            case(2):
            return (value + 100)/(200);
            case(3):
            return (value)/(47.62);
            case(4):
            return (value - 0.1)/(99.9);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaSubSynth") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value)/(100);
            case(2):
            return (value - 10)/(310);
            case(3):
            return (value)/(100);
            case(4):
            return (value + 60)/60;
            case(5):
            return (value - 1)/(1568);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaTalkBox") == 0) {
        switch(port) {
            case(0):
            return (value)/(200);
            case(1):
            return (value)/(200);
            case(2):
            return (value);
            case(3):
            return pow((value - 5)/(95), 0.5);
        }
    }
    //else if(strcmp(effect->getUniqueID(), "mdaTestTone") == 0) {

    //}
    else if(strcmp(effect->getUniqueID(), "mdaThruZero") == 0) {
        switch(port) {
            case(0):
            return 1 - ((value - 0.1)/(93.24));
            case(1):
            return (value)/(45.35);
            case(2):
            return (value)/(100);
            case(3):
            return (value + 100)/(200);
            case(4):
            return (value)/(100);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaTracker") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value)/(100);
            case(2):
            return (value)/(100);
            case(3):
            return (value)/(100);
            case(4):
            return (value + 36)/(72);
            case(5):
            return (value - 39)/(7311);
            case(6):
            return (value + 60)/(60);
            case(7):
            return (value + 20)/(40);
        }
    }
    else if(strcmp(effect->getUniqueID(), "mdaTransient") == 0) {
        switch(port) {
            case(0):
            return (value + 100)/(200);
            case(1):
            return (value + 100)/(200);
            case(2):
            return (value + 20)/(40);
            case(3):
            return (value + 10)/(20);
            case(4):
            return (value)/(100);
            case(5):
            return (value)/(100);

        }
    }
    //else if(strcmp(effect->getUniqueID(), "mdaVocInput") == 0) {

    //}
    else if(strcmp(effect->getUniqueID(), "mdaVocoder") == 0) {
        switch(port) {
            case(0):
            return (value);
            case(1):
            return (value + 20)/(40);
            case(2):
            return (value)/(100);
            case(3):
            return (value)/(100);
            case(4):
            return (value - 14)/(9986);
            case(5):
            return (value)/(100);
            case(6):
            return (value - 200)/(1400);
            case(7):
            return (value);
        }
    }
    return value;
}






extern "C" {

/* Plugin */

typedef struct {
    PLUGIN_CLASS* effect;
    float*        controls;
    float**       control_buffers;
    float**       inputs;
    float**       outputs;
} LVZPlugin;

static void
lvz_cleanup(LV2_Handle instance)
{
    LVZPlugin* plugin = (LVZPlugin*)instance;
    free(plugin->controls);
    free(plugin->control_buffers);
    free(plugin->inputs);
    free(plugin->outputs);
    delete plugin->effect;
    free(plugin);
}

static void
lvz_connect_port(LV2_Handle instance, uint32_t port, void* data)
{
    LVZPlugin*     plugin      = (LVZPlugin*)instance;
    const uint32_t num_params  = plugin->effect->getNumParameters();
    const uint32_t num_inputs  = plugin->effect->getNumInputs();
    const uint32_t num_outputs = plugin->effect->getNumOutputs();

    if (port < num_params) {
        plugin->control_buffers[port] = (float*)data;
    } else if (port < num_params + num_inputs) {
        plugin->inputs[port - num_params] = (float*)data;
    } else if (port < num_params + num_inputs + num_outputs) {
        plugin->outputs[port - num_params - num_inputs] = (float*)data;
    } else if (port == num_params + num_inputs + num_outputs) {
        plugin->effect->setEventInput((LV2_Atom_Sequence*)data);
    }
}

static int
master_callback(int, int ver, int, int, int, int)
{
    return 0;
}

static LV2_Handle
lvz_instantiate(const LV2_Descriptor*    descriptor,
                double                   rate,
                const char*              bundle_path,
                const LV2_Feature*const* features)
{
    PLUGIN_CLASS* effect = new PLUGIN_CLASS(master_callback);
    effect->setURI(URI_PREFIX PLUGIN_URI_SUFFIX);
    effect->setSampleRate(rate);

    uint32_t num_params  = effect->getNumParameters();
    uint32_t num_inputs  = effect->getNumInputs();
    uint32_t num_outputs = effect->getNumOutputs();

    LVZPlugin* plugin = (LVZPlugin*)malloc(sizeof(LVZPlugin));
    plugin->effect = effect;

    for (int i = 0; features[i]; ++i) {
        if (!strcmp(features[i]->URI, LV2_URID__map)) {
            LV2_URID_Map* map = (LV2_URID_Map*)features[i]->data;
            plugin->effect->setMidiEventType(
                map->map(map->handle, LV2_MIDI__MidiEvent));
            break;
        }
    }

    if (num_params > 0) {
        plugin->controls        = (float*)malloc(sizeof(float) * num_params);
        plugin->control_buffers = (float**)malloc(sizeof(float*) * num_params);
        for (uint32_t i = 0; i < num_params; ++i) {
            plugin->controls[i] = effect->getParameter(i);
            plugin->control_buffers[i] = NULL;
        }
    } else {
        plugin->controls        = NULL;
        plugin->control_buffers = NULL;
    }

    if (num_inputs > 0) {
        plugin->inputs = (float**)malloc(sizeof(float*) * num_inputs);
        for (uint32_t i = 0; i < num_inputs; ++i) {
            plugin->inputs[i] = NULL;
        }
    } else {
        plugin->inputs = NULL;
    }

    if (num_outputs > 0) {
        plugin->outputs = (float**)malloc(sizeof(float*) * num_outputs);
        for (uint32_t i = 0; i < num_outputs; ++i) {
            plugin->outputs[i] = NULL;
        }
    } else {
        plugin->outputs = NULL;
    }

    return (LV2_Handle)plugin;
}

static void
lvz_run(LV2_Handle instance, uint32_t sample_count)
{
    LVZPlugin* plugin = (LVZPlugin*)instance;

    for (int32_t i = 0; i < plugin->effect->getNumParameters(); ++i) {
        float val = plugin->control_buffers[i][0];
        if (val != plugin->controls[i]) {
            printf("valor: %f\n", translateParameter(plugin->effect, i, val));
            plugin->effect->setParameter(i, translateParameter(plugin->effect, i, val));
            plugin->controls[i] = val;
        }
    }

    plugin->effect->processReplacing(plugin->inputs, plugin->outputs, sample_count);
}

static const void*
lvz_extension_data(const char* uri)
{
    return NULL;
}

static void
lvz_deactivate(LV2_Handle instance)
{
    LVZPlugin* plugin = (LVZPlugin*)instance;
    plugin->effect->suspend();
}

/* Library */

static LV2_Descriptor descriptor;
static bool           initialised = false;

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    if (!initialised) {
        descriptor.URI            = URI_PREFIX PLUGIN_URI_SUFFIX;
        descriptor.instantiate    = lvz_instantiate;
        descriptor.connect_port   = lvz_connect_port;
        descriptor.activate       = NULL;
        descriptor.run            = lvz_run;
        descriptor.deactivate     = lvz_deactivate;
        descriptor.cleanup        = lvz_cleanup;
        descriptor.extension_data = lvz_extension_data;
        initialised = true;
    }

    switch (index) {
    case 0:
        return &descriptor;
    default:
        return NULL;
    }
}

/** Entry point for LVZ gendata */
LV2_SYMBOL_EXPORT
AudioEffectX*
lvz_new_audioeffectx()
{
    PLUGIN_CLASS* effect = new PLUGIN_CLASS(master_callback);
    effect->setURI(URI_PREFIX PLUGIN_URI_SUFFIX);
    return effect;
}

} // extern "C"
