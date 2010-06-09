// ==========================================================
// Tone mapping operator (Drago, 2003)
//
// Design and implementation by
// - Hervé Drolon (drolon@infonie.fr)
// - Thomas Mansencal (kelsolaar_fool@hotmail.com)
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

#include "FreeImage.h"
#include "Utilities.h"
#include "ToneMapping.h"

/**
Converts HDR To LDR.
@param src Input RGB16 or RGB[A]F image
@param gamma Gamma correction (gamma > 0). 1 means no correction, 2.2 in the original paper.
@param exposure Exposure parameter (0 means no correction, 0 in the original paper)
@return Returns a 24-bit RGB image if successful, returns NULL otherwise
*/
FIBITMAP* DLL_CALLCONV 
FreeImage_HDRLabs_ConvertToLdr(FIBITMAP *src, double gamma, double exposure) {
	if(!src) return NULL;

	// working RGBF variable
	FIBITMAP *dib = NULL;

	dib = FreeImage_ConvertToRGBF(src);
	if(!dib) return NULL;

	/*if(gamma != 1) {
		// perform gamma correction
		REC709GammaCorrection(dib, (float)gamma);
	}*/

	// clamp image highest values to display white, then convert to 24-bit RGB
	FIBITMAP *dst = ClampConvertRGBFTo24(dib);

	// clean-up and return
	FreeImage_Unload(dib);

	// copy metadata from src to dst
	FreeImage_CloneMetadata(dst, src);
	
	return dst;
}
