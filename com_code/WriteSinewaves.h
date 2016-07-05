#ifndef WriteSinewaves_H__
#define WriteSinewaves_H__

#include "adidat/include/ADIDataObject_h.h"  //IADIDataClass

//This example illustrates efficiently adding individual samples to each channel.
//This is particularly useful for situations where the source data has the samples interleaved
//across channels , as would commonly be the case when reading samples from a text file,
//or a sound card.
void gWriteSinewavesFromInterleavedChannelData(IADIDataClass *dataClassObj, const wchar_t *fileName);

//This example illustrates efficiently adding buffers of samples to each channel.
void gWriteSinewavesFromChannelData(IADIDataClass *dataClassObj, const wchar_t *fileName);

#endif