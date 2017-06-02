#ifndef VOC_DEMO
#define VOC_DEMO

#ifdef __cplusplus
extern "C" {
#endif

#include <soundpipe.h>
#include "voc.h"

enum {
VOC_NONE,
VOC_TONGUE
}; 

typedef struct {
    sp_data *sp;
    sp_voc *voc;
    SPFLOAT *tract;
    SPFLOAT *freq;
    SPFLOAT *velum;
    uint32_t tract_size;
    SPFLOAT gain;
    int mode;
    SPFLOAT tongue_pos;
    SPFLOAT tongue_diam;
} voc_demo_d;

void voc_demo_setup(voc_demo_d *vd);
void voc_demo_start(voc_demo_d *vd);
void voc_demo_stop(voc_demo_d *vd);
void voc_demo_destroy(voc_demo_d *vd);

#ifdef __cplusplus
}
#endif

#endif
