/*============================================================*//*============================================================*//*==														==*//*==				Universal Utility Routines				==*//*==														==*//*============================================================*//*============================================================*//*========================================================  Includes  */#include "UnivUtilities.h"/*========================================================  Local Variables  */short		wasMenuBarHeight;/*========================================================  Functions  *//*========================================================  CenterDialog  */void CenterDialog (short dialogID){	DialogTHndl		dlogHandle;	Rect			scrnRect, dlogBounds;	short			hPos, vPos;	Byte			wasState;		scrnRect = screenBits.bounds;	scrnRect.top += GetMBarHeight();		dlogHandle = (DialogTHndl)GetResource('DLOG', dialogID);	if (dlogHandle != kNilPointer)	{		wasState = HGetState((Handle)dlogHandle);		HLock((Handle)dlogHandle);				dlogBounds = (**dlogHandle).boundsRect;		OffsetRect(&dlogBounds, -dlogBounds.left, -dlogBounds.top);				hPos = ((scrnRect.right - scrnRect.left) - dlogBounds.right) / 2;		vPos = ((scrnRect.bottom - scrnRect.top) - dlogBounds.bottom) / 3;				OffsetRect(&dlogBounds, hPos, vPos + GetMBarHeight());				(**dlogHandle).boundsRect = dlogBounds;		HSetState((Handle)dlogHandle, wasState);	}}/*========================================================  CenterAlert  */void CenterAlert (short alertID){	AlertTHndl		alertHandle;	Rect			scrnRect, alertRect;	short			horiOff, vertOff;	Byte			wasState;		scrnRect = screenBits.bounds;	scrnRect.top += GetMBarHeight();		alertHandle = (AlertTHndl)GetResource('ALRT', alertID);	if (alertHandle != kNilPointer)	{		wasState = HGetState((Handle)alertHandle);		HLock((Handle)alertHandle);				alertRect = (**alertHandle).boundsRect;		OffsetRect(&alertRect, -alertRect.left, -alertRect.top);				horiOff = ((scrnRect.right - scrnRect.left) - alertRect.right) / 2;			vertOff = ((scrnRect.bottom - scrnRect.top) - alertRect.bottom) / 3;				OffsetRect(&alertRect, horiOff, vertOff + GetMBarHeight());				(**alertHandle).boundsRect = alertRect;		HSetState((Handle)alertHandle, wasState);	}}/*========================================================  FlashDialogButton  */void FlashDialogButton (DialogPtr theDialog, short itemNumber){	Rect			itemRect;	Handle			itemHandle;	long			dummyLong;	short			itemType;		GetDItem(theDialog, itemNumber, &itemType, &itemHandle, &itemRect);	HiliteControl((ControlHandle)itemHandle, inButton);	Delay(8, &dummyLong);	HiliteControl((ControlHandle)itemHandle, 0);}/*========================================================  DrawDefaultButton  */void DrawDefaultButton (DialogPtr theDialog, short itemNumber){	Rect			itemRect;	Handle			itemHandle;	short			itemType;		GetDItem(theDialog, itemNumber, &itemType, &itemHandle, &itemRect);	InsetRect(&itemRect, -4, -4);	PenSize(3, 3);	FrameRoundRect(&itemRect, 19, 19);	PenNormal();}/*========================================================  SetDialogString  */void SetDialogString (DialogPtr theDialog, short item, StringPtr theString){	Rect			itemRect;	Handle			itemHandle;	short			itemType;		GetDItem(theDialog, item, &itemType, &itemHandle, &itemRect);	SetIText(itemHandle, theString);}/*========================================================  SetDialogNumToStr  */void SetDialogNumToStr (DialogPtr theDialog, short item, long theNumber){	Str255			theString;	Rect			itemRect;	Handle			itemHandle;	short			itemType;		NumToString(theNumber, theString);	GetDItem(theDialog, item, &itemType, &itemHandle, &itemRect);	SetIText(itemHandle, theString);}/*========================================================  SelectFromRadioGroup  */void SelectFromRadioGroup (DialogPtr theDialog, short setItem, short fromItem, short toItem){	Rect			iRect;	Handle			iHandle;	short			iType, i;		for (i = fromItem; i <= toItem; i++)	{		GetDItem(theDialog, i, &iType, &iHandle, &iRect);		SetCtlValue((ControlHandle)iHandle, (short)FALSE);	}		GetDItem(theDialog, setItem, &iType, &iHandle, &iRect);	SetCtlValue((ControlHandle)iHandle, (short)TRUE);}/*========================================================  EnableControl  */void EnableControl(DialogPtr theDialog, short whichItem){	Rect			iRect;	Handle			iHandle;	short			iType;		GetDItem(theDialog, whichItem, &iType, &iHandle, &iRect);	HiliteControl((ControlHandle)iHandle, kActive);}/*========================================================  DisableControl  */void DisableControl(DialogPtr theDialog, short whichItem){	Rect			iRect;	Handle			iHandle;	short			iType;		GetDItem(theDialog, whichItem, &iType, &iHandle, &iRect);	HiliteControl((ControlHandle)iHandle, kInactive);}/*========================================================  LocalToGlobalRect  */void LocalToGlobalRect (Rect *theRect){	Point			upperLeftPt;		upperLeftPt.h = 0;	upperLeftPt.v = 0;	LocalToGlobal(&upperLeftPt);	OffsetRect(theRect, upperLeftPt.h, upperLeftPt.v);}/*========================================================  GlobalToLocalRect  */void GlobalToLocalRect (Rect *theRect){	Point			upperLeftPt;		upperLeftPt.h = 0;	upperLeftPt.v = 0;	GlobalToLocal(&upperLeftPt);	OffsetRect(theRect, upperLeftPt.h, upperLeftPt.v);}/*========================================================  ZoomOutDialogRect  */void ZoomOutDialogRect (short dialogID){	#define			kSteps		20	#define			kZoomDelay	1	DialogTHndl		dlogHandle;	GrafPtr			wasPort;	WindowPtr		windowInFront;	Rect			dlogBounds, zoomRect;	long			dummyLong;	Byte			wasState;	short			wideStep, highStep, i;		GetPort(&wasPort);	windowInFront = FrontWindow();	SetPort((GrafPtr)windowInFront);		dlogHandle = (DialogTHndl)GetResource('DLOG', dialogID);	if (dlogHandle != kNilPointer)	{		wasState = HGetState((Handle)dlogHandle);		HLock((Handle)dlogHandle);		dlogBounds = (**dlogHandle).boundsRect;		HSetState((Handle)dlogHandle, wasState);	}		wideStep = ((dlogBounds.right - dlogBounds.left) / 2) / kSteps;	highStep = ((dlogBounds.bottom - dlogBounds.top) / 2) / kSteps;		SetRect(&zoomRect, dlogBounds.left + (wideStep * kSteps), 			dlogBounds.top + (highStep * kSteps), 			dlogBounds.right - (wideStep * kSteps), 			dlogBounds.bottom - (highStep * kSteps));	GlobalToLocalRect(&zoomRect);		PenPat(gray);	PenMode(patXor);		for (i = 0; i < kSteps; i++)	{		FrameRect(&zoomRect);		Delay(kZoomDelay, &dummyLong);		FrameRect(&zoomRect);		InsetRect(&zoomRect, -wideStep, -highStep);	}		PenNormal();	SetPort((GrafPtr)wasPort);}/*========================================================  PasStringCopy  */void PasStringCopy (StringPtr p1, StringPtr p2){	register short		stringLength;		stringLength = *p2++ = *p1++;	while (--stringLength >= 0)		*p2++ = *p1++;}/*========================================================  PasStringCopyNum  */void PasStringCopyNum (StringPtr p1, StringPtr p2, short charsToCopy){	short			charsCopied;		if (charsToCopy > *p1)		charsToCopy = *p1;		*p2 = charsToCopy;		*p2++;	*p1++;		charsCopied = charsToCopy + 1;		while (--charsCopied >= 0)		*p2++ = *p1++;}/*========================================================  PasStringConcat  */void PasStringConcat (StringPtr p1, StringPtr p2){	short		wasLength, addedLength, i;		wasLength = *p1;	if (wasLength > 255)		wasLength = 255;		addedLength = *p2;	if ((wasLength + addedLength) > 255)		addedLength = 255 - wasLength;		*p1 = wasLength + addedLength;		*p1++;	*p2++;		for (i = 0; i < wasLength; i++)		*p1++;		for (i = 0; i < addedLength; i++)		*p1++ = *p2++;}/*========================================================  RandomInt  */short RandomInt (short range){	register long	rawResult;		rawResult = Random();	if (rawResult < 0)		rawResult *= -1;	return (rawResult * (long)range / 32768);}/*========================================================  RandomCoin  */Boolean RandomCoin (void){	register long	rawResult;		rawResult = Random() & 0x00000001;		return ((Boolean)rawResult);}/*========================================================  DeathError  */void DeathError (short errorNumber){	short			dummyInt;	Str255			errTitle, errMessage, errNumberString, errExtra;		InitCursor();		if (errorNumber > 1)	{		GetIndString((StringPtr)&errTitle, rErrTitleID, errorNumber);		GetIndString((StringPtr)&errMessage, rErrMssgID, errorNumber);	}	else	{		GetIndString((StringPtr)&errTitle, rErrTitleID, 1);		GetIndString((StringPtr)&errMessage, rErrMssgID, 1);	}	NumToString((long)errorNumber, (StringPtr)&errNumberString);	ParamText((StringPtr)&errTitle, (StringPtr)&errMessage, 			(StringPtr)&errNumberString, "\p");	CenterAlert(rDeathAlertID);		dummyInt = Alert(rDeathAlertID, kNilPointer);		ExitToShell();}/*========================================================  MinorError  */void MinorError (short errorNumber){	short			dummyInt;	Str255			errMessage;		InitCursor();		GetIndString((StringPtr)&errMessage, rMinorErrMssgID, errorNumber);	ParamText((StringPtr)&errMessage, (StringPtr)"\p", (StringPtr)"\p", (StringPtr)"\p");		CenterAlert(rMinorAlertID);		dummyInt = Alert(rMinorAlertID, kNilPointer);}/*========================================================  SimpleMessage  */void SimpleMessage (void){	}/*========================================================  KeyIsDown  */Boolean KeyIsDown (short keyCodeOffset){	KeyMap			theKeyMap;	Boolean			isSet;		GetKeys(theKeyMap);    isSet = (BitTst(&theKeyMap, keyCodeOffset) != 0);	return(isSet);}/*========================================================  CommandKeyIsDown  */Boolean CommandKeyIsDown (void){	KeyMap			theKeyMap;	Boolean			isSet;		GetKeys(theKeyMap);	isSet = (BitTst(&theKeyMap, kCommandKeyMap) != 0);	return(isSet);}/*========================================================  OptionKeyIsDown  */Boolean OptionKeyIsDown (void){	KeyMap			theKeyMap;	Boolean			isSet;		GetKeys(theKeyMap);    isSet = (BitTst(&theKeyMap, kOptionKeyMap) != 0);	return(isSet);}/*========================================================  CommandPeriodDown  */Boolean CommandPeriodDown (void){	KeyMap			theKeyMap;	Boolean			isSet;		GetKeys(theKeyMap);    isSet = (BitTst(&theKeyMap, kCommandKeyMap) != 0) &&     		(BitTst(&theKeyMap, kPeriodKeyMap) != 0);	return(isSet);}/*========================================================  RectFromWindow  */void RectFromWindow (Rect *boundsRect, WindowPtr theWindow){	Point			tempPt;		if (theWindow != kNilPointer)	{		*boundsRect = (*theWindow).portRect;		SetPt(&tempPt, 0, 0);		LocalToGlobal(&tempPt);		OffsetRect(&(*boundsRect), tempPt.h, tempPt.v);		(*boundsRect).top -= 10;	}	else	{		SetRect(boundsRect, 0, 0, 0, 0);	}}/*========================================================  GetRect  */OSErr GetRect (Rect *theRect, short rectID){	Handle			theRectHandle;	char			wasState;		theRectHandle = GetResource('RECT', rectID);	/* get a 'RECT' type resource */	if (theRectHandle != kNilPointer)				/* be it there? */	{		wasState = HGetState(theRectHandle);		HLock(theRectHandle);						/* lock it! */		BlockMove(*theRectHandle, theRect, 8);		/* move  data into a rect struct */		HSetState(theRectHandle, wasState);		return (MemError());	}	else											/* return the non-rect */	{		SetRect(theRect, 0, 0, 0, 0);				/* and this is a non-rect */		return (ResError());	}}/*========================================================  ShowMenuBar  */void ShowMenuBar (WindowPtr theWindow){		if (GetMBarHeight() == 0)	{		LMSetMBarHeight(wasMenuBarHeight);		DrawMenuBar();	}}/*========================================================  HideMenuBar  */void HideMenuBar (WindowPtr theWindow){		if (GetMBarHeight() != 0)	{		wasMenuBarHeight = GetMBarHeight();		LMSetMBarHeight(0);	}}/*========================================================  USSecsToDateString  */void USSecsToDateString (long theSecs, StringPtr theDate){	Str255			theDay, theMonth, theYear;	DateTimeRec		theDateRec;		Secs2Date(theSecs, &theDateRec);		NumToString((long)(theDateRec.day), theDay);	NumToString((long)(theDateRec.month), theMonth);	NumToString((long)(theDateRec.year % 100), theYear);		PasStringConcat(theMonth, "\p/");	PasStringConcat(theMonth, theDay);	PasStringConcat(theMonth, "\p/");	PasStringConcat(theMonth, theYear);		PasStringCopy((StringPtr)theMonth, (StringPtr)theDate);}/*========================================================  IntlSecsToDateString  */void IntlSecsToDateString (long theSecs, StringPtr theDate){	Str255			theDay, theMonth, theYear;	DateTimeRec		theDateRec;		Secs2Date(theSecs, &theDateRec);		NumToString((long)(theDateRec.day), theDay);	NumToString((long)(theDateRec.month), theMonth);	NumToString((long)(theDateRec.year % 100), theYear);		PasStringConcat(theDay, "\p/");	PasStringConcat(theDay, theMonth);	PasStringConcat(theDay, "\p/");	PasStringConcat(theDay, theYear);		PasStringCopy((StringPtr)theDay, (StringPtr)theDate);}/*========================================================  HoldIt  */void HoldIt (short ticksToWait){	long			dummyLong;		Delay(ticksToWait, &dummyLong);}/*========================================================  GetOrigin  */void GetOrigin (Point *theOrigin){	theOrigin->h = 0;	theOrigin->v = 0;	LocalToGlobal(theOrigin);	theOrigin->h *= -1;	theOrigin->v *= -1;}/*========================================================  SetMouse  */void SetMouse (Point newMouse){	#define		MTemp		0x828	/* Low-level interrupt mouse location [long] */	#define		RawMouse	0x82C	/* un-jerked mouse coordinates [long] */	#define		CrsrNew		0x8CE	/* Cursor changed? [byte] */	long		longPoint;	long		*pointPtr;	short		*shortPtr;		BlockMove(&newMouse, &longPoint, 4);		pointPtr = (long *)RawMouse;	*pointPtr = longPoint;		pointPtr = (long *)MTemp;	*pointPtr = longPoint;		shortPtr = (short *)CrsrNew;	*shortPtr = 0xFFFF;}/*========================================================  ForcePointInRect  */Boolean ForcePointInRect(Point *thePoint, Rect *theBounds){	Boolean			pointMoved = FALSE;		if (thePoint->h < theBounds->left)	{		thePoint->h = theBounds->left;		pointMoved = TRUE;	}	else if (thePoint->h > theBounds->right)	{		thePoint->h = theBounds->right;		pointMoved = TRUE;	}		if (thePoint->v < theBounds->top)	{		thePoint->v = theBounds->top;		pointMoved = TRUE;	}	else if (thePoint->v > theBounds->bottom)	{		thePoint->v = theBounds->bottom;		pointMoved = TRUE;	}		return (pointMoved);}/*========================================================  GetChooserName  */void GetChooserName (StringPtr thisName){	#define		kChooserStringID	-16096		PasStringCopy(*GetString(kChooserStringID), thisName);	if (thisName == kNilPointer)	{		thisName[0] = 0;	}}