/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
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
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#pragma once

#include <UModalDialogs.h>

#include "PascalString.h"

#include "xp_core.h"

const ResIDT cDefaultTextTraitsID = 128;
const ResIDT cPasswordTextTraitsID = 4000;

const Int16 cDialogSpacing = 13;

const PaneIDT	PaneID_AlertCaption 	= 	'capt';
const PaneIDT	PaneID_AlertIcon		=	'icon';
const PaneIDT	PaneID_AlertEditField	=	'edit';
const PaneIDT	PaneID_PasswordEditName =	'name';
const PaneIDT	PaneID_PasswordEditPass	=	'pass';
const PaneIDT	PaneID_MessageCaption	=	'mesg';


enum {
	WIND_NameAndPassword				=	16000,
	WIND_Password,
	WIND_StandardAlert,
	WIND_Resizeable,
	WIND_OkCancelAlert,
	WIND_BigMessageAlert,
	WIND_MessageDialog,		// for non-alert uses of FE_Alert
	WIND_CheckConfirmDialog
};


enum EAlertType {
	eAlertTypeStop = 1,
	eAlertTypeNote,
	eAlertTypeCaution,
	eAlertTypeError
};

enum EAlertIconID {
	eAlertIconStop = 10000,
	eAlertIconNote,
	eAlertIconCaution,
	eAlertIconError = eAlertIconCaution
};

enum {
	FORMAT_TEXT,
	FORMAT_HTML
};

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

class StStdDialogHandler : public StDialogHandler
{
		enum {
			noAutoCenter					= 0x0000,
			centerMainScreen				= 0x280A,
			alertPositionMainScreen			= 0x300A,
			staggerMainScreen				= 0x380A,
			centerParentWindow				= 0xA80A,
			alertPositionParentWindow		= 0xB00A,
			staggerParentWindow				= 0xB80A,
			centerParentWindowScreen		= 0x680A,
			alertPositionParentWindowScreen	= 0x700A,
			staggerParentWindowScreen		= 0x780A
		};

	public:
							StStdDialogHandler(
									ResIDT				inDialogID,
									LCommander* 		inSuper);
									
		void				SetInitialDialogPosition(LWindow* inParentWindow);
		virtual	MessageT	WaitUserResponse(void);

		void				SetCaption(ConstStringPtr inCaption);
	
		// Handy macros
		LPane*				GetPane(PaneIDT id);
		LPane*				GetControl(PaneIDT id) { return (LControl*)GetPane(id); }
		void				HidePane(PaneIDT id);
		void				ShowPane(PaneIDT id);
		void				EnablePane(PaneIDT id);
		void				DisablePane(PaneIDT id);
		void				SetValue(PaneIDT id, Int32 value);
		Int32				GetValue(PaneIDT id);
		void				SetBoolean(PaneIDT id, Boolean value);
		Boolean				GetBoolean(PaneIDT id);
		void				SetText(PaneIDT id, ConstStr255Param value);
		void				SetNumberText(PaneIDT id, SInt32 value);
		void				GetText(PaneIDT id, Str255 value);
		SInt32				GetNumberText(PaneIDT id);
		void 				CopyTextValue(PaneIDT fromPaneId, PaneIDT toPaneId);
		void				CopyNumberValue(PaneIDT fromPaneId, PaneIDT toPaneId);

	protected:

		void				CalcDialogTargetBounds(
								Int16 					inPlacement,
								LWindow*				inParentWindow,
								Rect&					outBounds);

		Int16				CalcDialogPlacement(void);

	private:

		ResIDT				mDialogResID;
};

class StAlertHandler : public StStdDialogHandler
{
	public:
						StAlertHandler(
								ConstStringPtr		 	inAlertText,
								EAlertType				inAlertType,
								LCommander*				inSuper);
								
						StAlertHandler(
								ResIDT					inStrListID,
								Int16 					inIndex,
								EAlertType				inAlertType,
								LCommander*				inSuper);
	protected:
		
		void			SetAlertTitle(ConstStringPtr inTitle);
		void			SetAlertIcon(EAlertType	inAlertType);
};

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

class StAutoSizingDialog : public StStdDialogHandler
{
	public:
						StAutoSizingDialog(
								ResIDT					inDialogID,
								const CString&	inAlertText,
								const CString&	inDefaultEditText,
								LCommander*				inSuper);

		void			SetInitialDialogSize(void);
};

// ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ

class UStdDialogs
{
	public:
		static void		Alert(
								ConstStringPtr		inAlertText,
								EAlertType			inType,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL,
								LStr255*			inWindowTitle = NULL
								);
		
		static Boolean	AskWithCustomButtons(
								ConstStringPtr 		inQuestion,
								ConstStringPtr		inDefaultTextBtn = nil,
								ConstStringPtr		inCancelTextBtn = nil,
								LWindow*			inOverWindow = nil,
								LCommander*			inSuper = nil,
								LStr255*			inWindowTitle = nil
								);
								
		static Boolean 	AskOkCancel(
								ConstStringPtr		inQuestion,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL,
								LStr255*			inWindowTitle = NULL);

		static Boolean	AskStandardTextPrompt(
								const CStr255&		inTitleText,
								const CStr255&		inPromptText,
								CString&			ioString,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL,
								Int32 				maxIOStringSize = 255);

		static Boolean	AskForPassword(
								const CString&		inPromptText,
								CString&			ioPassString,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL);

		static Boolean	AskForNameAndPassword(
								const CString&	inPromptText,
								CString&	ioNameString,
								CString&	ioPassString,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL);


		static Boolean	CheckConfirm(
								const CString&		pConfirmMessage,
								const CString&		pCheckMessage,
								const CString&		pOKMessage,
								const CString&		pCancelMessage,
								XP_Bool*			pChecked,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL);


		static Boolean	SelectDialog(
								const CString&		pMessage,
								const char**		pList,
								int16*				pCount,
								LWindow*			inOverWindow = NULL,
								LCommander*			inSuper = NULL);


		static OSErr	AskSaveAsTextOrSource(
								StandardFileReply& 	ioReply,
								const CString& initialFilename,
								Int16& 				ioFormat);

		static OSErr	AskSaveAsSource(
								StandardFileReply& 	ioReply,
								const CString& initialFilename,
								Int16& 				ioFormat);
						

		static OSErr	AskUploadAsDataOrMacBin(
								StandardFileReply& 	ioReply,
								Int16& 				ioFormat);

		static Boolean 	TryToInteract(Int32 inForSeconds = -1);

// FIX ME -- this is commented out to get editor to compile						 
//	protected:
	
			// dialog hook function for CustomPutFile call
		static pascal short SaveAsHook( short item, DialogPtr dialog, void* dataPtr );
			// dialog hook function for CustomGetFile call
		static pascal short UploadAsHook( short item, DialogPtr dialog, void* dataPtr );
};
