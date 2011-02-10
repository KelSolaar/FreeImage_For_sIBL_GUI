// ==========================================================
// HDRLabs Functions.
//
// Design and implementation by
// - Hervé Drolon (drolon@infonie.fr)
// - Thomas Mansencal (thomas.mansencal@gmail.com)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================

#include <string.h>

#include "FreeImage.h"
#include "Utilities.h"
#include "ToneMapping.h"

/**
Converts An HDRI Bitmap To A LDRI One.
@param src Input RGB16 or RGB[A]F image.
@param gamma Gamma correction.
@return Returns a 24-bit RGB image if successful, returns NULL otherwise.
*/
FIBITMAP* DLL_CALLCONV 
FreeImage_HDRLabs_ConvertToLdr(FIBITMAP *src, double gamma) {
	if(!src) return NULL;

	FIBITMAP *dib = NULL;

	dib = FreeImage_ConvertToRGBF(src);
	if(!dib) return NULL;

	if(gamma != 1) {
		REC709GammaCorrection(dib, (float)gamma);
	}
	
	FIBITMAP *dst = ClampConvertRGBFTo24(dib);

	FreeImage_Unload(dib);
	
	FreeImage_CloneMetadata(dst, src);

	FreeImage_Unload(src);
	
	return dst;
}