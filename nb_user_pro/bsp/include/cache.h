#ifndef __CACHE_H__
#define __CACHE_H__

void Dd_Cache_Enable(void);
void Dd_Cache_Disable(void);
void Dd_Cache_SetCacheableMemRGN(u32 srcaddr ,u32 dstaddr);
void Dd_Cache_SetCacheableMemRGN1(u32 srcaddr ,u32 dstaddr);

#endif

