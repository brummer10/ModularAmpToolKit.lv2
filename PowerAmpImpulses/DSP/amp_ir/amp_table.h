
struct AmpDesc
{
  int32_t ir_count;
  uint32_t ir_sr;
  float ir_data[];
};

template <int32_t tab_size>
struct AmpDesc_imp
{
  int32_t ir_count;
  uint32_t ir_sr;
  float ir_data[tab_size];
  operator AmpDesc&()
  {
    return *(AmpDesc*)this;
  }
};

#include "Blackat_Leon_S7.cc"
#include "Cicognani_Imperivm_Luxury.cc"
#include "DV_Mark_Triple_6.cc"
#include "Engl_Retro_Tube.cc"
#include "Engl_Special_Edition.cc"
#include "EVH_5150_III.cc"
#include "Fortin_Natas.cc"
#include "Kaos_Sludge_15.cc"
#include "Krank_Krankenstein.cc"
#include "Laney_ironheart.cc"
#include "MakosampCustomHatred.cc"
#include "Marshall_JMP_2203__Jose_Arredondo_mod.cc"
#include "Marshall_MG_15.cc"
#include "Mesa_Boogie_Mark_V.cc"
#include "Peavey_Vypyr_15.cc"
#include "Randall_Satan.cc"
#include "Randall_thrasher.cc"
#include "Splawn_Nitro.cc"
#include "Splawn_Quick_Rod.cc"
#include "Taurus_Stomphead.cc"

struct AmpEntry {
    AmpDesc *data;
} amp_table[] = {
    { &static_cast<AmpDesc&>(data_Blackat_Leon_S7) },
    { &static_cast<AmpDesc&>(data_Cicognani_Imperivm_Luxury) },
    { &static_cast<AmpDesc&>(data_DV_Mark_Triple_6) },
    { &static_cast<AmpDesc&>(data_Engl_Retro_Tube) },
    { &static_cast<AmpDesc&>(data_Engl_Special_Edition) },
    { &static_cast<AmpDesc&>(data_EVH_5150_III) },
    { &static_cast<AmpDesc&>(data_Fortin_Natas) },
    { &static_cast<AmpDesc&>(data_Kaos_Sludge_15) },
    { &static_cast<AmpDesc&>(data_Krank_Krankenstein) },
    { &static_cast<AmpDesc&>(data_Laney_ironheart) },
    { &static_cast<AmpDesc&>(data_MakosampCustomHatred) },
    { &static_cast<AmpDesc&>(data_Marshall_JMP_2203__Jose_Arredondo_mod) },
    { &static_cast<AmpDesc&>(data_Marshall_MG_15) },
    { &static_cast<AmpDesc&>(data_Mesa_Boogie_Mark_V) },
    { &static_cast<AmpDesc&>(data_Peavey_Vypyr_15) },
    { &static_cast<AmpDesc&>(data_Randall_Satan) },
    { &static_cast<AmpDesc&>(data_Randall_thrasher) },
    { &static_cast<AmpDesc&>(data_Splawn_Nitro) },
    { &static_cast<AmpDesc&>(data_Splawn_Nitro) },
    { &static_cast<AmpDesc&>(data_Taurus_Stomphead) },
};
static const unsigned int amp_table_size = sizeof(amp_table) / sizeof(amp_table[0]);

static AmpEntry& getAmpEntry(unsigned int n) {
    if (n >= amp_table_size) {
        n = amp_table_size - 1;
    }
    return amp_table[n];
}
