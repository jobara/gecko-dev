/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1999 Netscape Communications Corporation.  All Rights
 * Reserved.
 */


#ifndef nsAFMObject_h__
#define nsAFMObject_h__ 


#include "nsIFontMetrics.h"
#include "nsFont.h"
#include "nsString.h"
#include "nsUnitConversion.h"
#include "nsIDeviceContext.h"
#include "nsCRT.h"

class nsDeviceContextPS;


// AFM Key Words
typedef enum
{
  kComment,

  // File structure.
  kStartFontMetrics,
  kEndFontMetrics,
  kStartCompFontMetrics,
  kEndCompFontMetrics,
  kStartDescendent,
  kEndDescendent,
  kStartMasterFontMetrics,
  kEndMasterFontMetrics,

  // Control information.
  kMetricsSets,
  kDescendents,
  kMasters,
  kAxes,

  // Global font information. 
  kFontName,
  kFullName,
  kFamilyName,
  kWeight,
  kFontBBox,
  kVersion,
  kNotice,
  kEncodingScheme,
  kMappingScheme,
  kEscChar,
  kCharacterSet,
  kCharacters,
  kIsBaseFont,
  kVVector,
  kIsFixedV,
  kCapHeight,
  kXHeight,
  kAscender,
  kDescender,
  kWeightVector,
  kBlendDesignPositions,
  kBlendDesignMap,
  kBlendAxisTypes,


  // Writing direction information. 
  kStartDirection,
  kEndDirection,
  kUnderlinePosition,
  kUnderlineThickness,
  kItalicAngle,
  kCharWidth,
  kIsFixedPitch,

  // Individual character metrics. 
  kStartCharMetrics,
  kEndCharMetrics,
  kC,
  kCH,
  kWX,
  kW0X,
  kW1X,
  kWY,
  kW0Y,
  kW1Y,
  kW,
  kW0,
  kW1,
  kVV,
  kN,
  kB,
  kL,

  // Kerning data.
  kStartKernData,
  kEndKernData,
  kStartTrackKern,
  kEndTrackKern,
  kTrackKern,
  kStartKernPairs,
  kEndKernPairs,
  kKP,
  kKPH,
  kKPX,
  kKPY,

  // Composite character data.
  kStartComposites,
  kEndComposites,
  kCC,
  kPCC,

  // Axis information.
  kStartAxis,
  kEndAxis,
  kAxisType,
  kAxisLabel,


  // Master Design Information 
  kStartMaster,
  kEndMaster

} AFMKey;



// Single character infor for AFM character. 
struct AFM_Single_Char_Metrics
{

  PRInt32   mCharacter_Code;	// default charcode (-1 if not encoded) 
  double    mW0x;		          // character width x in writing direction 0 
  double    mW0y;		          // character width y in writing direction 0 
  double    mW1x;		          // character width x in writing direction 1 
  double    mW1y;		          // character width y in writing direction 1 
  char      *mName;	          // character name 
  double    mVv_x;	          // local VVector x 
  double    mVv_y;	          // local VVector y 

  // character bounding box. 
  double    mLlx;
  double    mLly;
  double    mUrx;
  double    mUry;

  double num_ligatures;

  //AFMLigature *ligatures;
};


typedef struct AFM_Single_Char_Metrics  AFMscm;


// Font information which we get from AFM files, this is needed for the PS output

struct fontInformation
{
  double  mFontVersion;
  char    *mFontName;
  char    *mFullName;
  char    *mFamilyName;
  char    *mWeight;
  double  mFontBBox_llx;
  double  mFontBBox_lly;
  double  mFontBBox_urx;
  double  mFontBBox_ury;
  char    *mVersion;
  char    *mNotice;
  char    *mEncodingScheme;
  PRInt32 mMappingScheme;
  PRInt32 mEscChar;
  char    *mCharacterSet;
  PRInt32 mCharacters;
  PRBool  mIsBaseFont;
  double  mVVector_0;
  double  mVVector_1;
  PRBool  mIsFixedV;
  double  mCapHeight;
  double  mXHeight;
  double  mAscender;
  double  mDescender;
  double  mUnderlinePosition;
  double  mUnderlineThickness;

  AFMscm *AFMCharMetrics;

};


typedef struct fontInformation AFMFontInformation;


class nsAFMObject 
{
public:

  /** ---------------------------------------------------
   * Construct and AFMObject
   * @update 2/26/99 dwc
   */
  nsAFMObject();

  /** ---------------------------------------------------
   * delete an AFMObject
   * @update 2/26/99 dwc
   */
 virtual ~nsAFMObject();

  /** ---------------------------------------------------
   * Initialize an AFMObject
   * @update 2/26/99 dwc
   * @param aFontName - A "C" string name of the font this object will get initialized to
   * @param aFontHeight -- The font size for this object
   */
  void    Init(char *aFontName,PRInt32  aFontHeight);


  /** ---------------------------------------------------
   * Calculate the width of a unicharacter string
   * @update 2/26/99 dwc
   * @param aString - The unicharacter string to get the width for
   * @param aWidth - Where the width of the string will be put.
   * @param aLenth - The length of the passed in string
   */
  void    GetStringWidth(const PRUnichar *aString,nscoord& aWidth,nscoord aLength);

  /** ---------------------------------------------------
   * Calculate the width of a C style string
   * @update 2/26/99 dwc
   * @param aString - The C string to get the width for
   * @param aWidth - Where the width of the string will be put.
   * @param aLenth - The length of the passed in string
   */
  void    GetStringWidth(const char *aString,nscoord& aWidth,nscoord aLength);

protected:
  /** ---------------------------------------------------
   * Read in and parse and AFM file
   * @update 2/26/99 dwc
   */
  void    AFM_ReadFile(void);

  /** ---------------------------------------------------
   * Get a Keyword in the AFM file being parsed
   * @update 2/26/99 dwc
   */
  void    GetKey(AFMKey *aTheKey);

  /** ---------------------------------------------------
   * Get a token from the AFM file
   * @update 2/26/99 dwc
   */
  PRInt32 GetToken(void);

  /** ---------------------------------------------------
   * For a given token, find the keyword it represents
   * @update 2/26/99 dwc
   */
  PRInt32 MatchKey(char *aKey);

  /** ---------------------------------------------------
   * Get a line from the currently parsed file
   * @update 2/26/99 dwc
   */
  PRInt32 GetLine(void);

  /** ---------------------------------------------------
   * Get a string from the currently parsed file
   * @update 2/26/99 dwc
   */
  char*   GetAFMString (void);

  /** ---------------------------------------------------
   * Get a word from the currently parsed file
   * @update 2/26/99 dwc
   */
  char*   GetAFMName (void); 

  /** ---------------------------------------------------
   * Get an integer from the currently parsed file
   * @update 2/26/99 dwc
   */
  void    GetAFMInt (PRInt32 *aInt) {GetToken();*aInt = atoi (mToken);}

  /** ---------------------------------------------------
   * Get a floating point number from the currently parsed file
   * @update 2/26/99 dwc
   */
  void    GetAFMNumber (double *aFloat){GetToken();*aFloat = atof (mToken);}

  /** ---------------------------------------------------
   * Get a boolean from the currently parsed file
   * @update 2/26/99 dwc
   */
  void    GetAFMBool (PRBool *aBool);

  /** ---------------------------------------------------
   * Read in the AFMFontInformation from the currently parsed AFM file
   * @update 2/26/99 dwc
   */
  void    ReadCharMetrics (AFMFontInformation *aFontInfo,PRInt32 aNumCharacters);

public:
  AFMFontInformation  *mPSFontInfo;


protected:
  FILE                *mAFMFile;          // this is the AFM file we are parsing.
  char                mToken[256];        // Temporary storage for reading and parsing the file
  nscoord             mFontHeight;        // font height in points that we are supporting.
                                          // XXX  This should be passed into the GetStringWidth
                                          // so we can have one font family support many sizes

};

#define NUM_KEYS (sizeof (keynames) / sizeof (struct keyname_st) - 1)

#endif

