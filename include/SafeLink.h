#pragma once

class  __declspec( dllexport ) CSafeLink
{
public :
	CSafeLink()
		: mpPrevNode(NULL)
		, mpNextNode(NULL)
	{
	}

	~CSafeLink()
	{
		if(mpPrevNode != NULL)
			mpPrevNode->NextLinkTo(mpNextNode) ;
		if(mpNextNode != NULL)
			mpNextNode->PrevLinkTo(mpPrevNode) ;
	}

	CSafeLink *NextLinkTo(CSafeLink *pNode)
	{
		CSafeLink *pOldNode = mpNextNode ;
		mpNextNode = pNode ;
		return pOldNode ;
	}

	CSafeLink *PrevLinkTo(CSafeLink *pNode)
	{
		CSafeLink *pOldNode = mpPrevNode ;
		mpPrevNode = pNode ;
		return pOldNode ;
	}

	inline virtual CSafeLink *GetNextNode()
	{
		return mpNextNode ;
	}

	inline virtual CSafeLink *GetPrevNode()
	{
		return mpPrevNode ;
	}

	void RemoveAllLinkedNode()
	{
		while(mpPrevNode != NULL)
			delete mpPrevNode ;
		while(mpNextNode != NULL)
			delete mpNextNode ;
	}

	void AddNodeToNextPos(CSafeLink *pNode)
	{
		if(mpNextNode != NULL)
		{
			pNode->NextLinkTo(mpNextNode) ;
			mpNextNode->PrevLinkTo(pNode) ;
		}
		pNode->PrevLinkTo(this) ;
		mpNextNode = pNode ;
	}

	void AddNodeToPrevPos(CSafeLink *pNode)
	{
		if(mpPrevNode != NULL)
		{
			mpPrevNode->NextLinkTo(pNode) ;
			pNode->PrevLinkTo(mpPrevNode) ;
		}
		pNode->NextLinkTo(this); 
		mpPrevNode = pNode ;
	}

	void AddNodeToEndPos(CSafeLink *pNode)
	{
		CSafeLink *pEndNode = this ;
		while(pEndNode->GetNextNode() != NULL)
			pEndNode = pEndNode->GetNextNode() ;
		pEndNode->NextLinkTo(pNode) ;
		if(pNode != NULL)
		{
			pNode->PrevLinkTo(pEndNode) ;
			pNode->NextLinkTo(NULL) ;
		}
	}

	void ReleaseFromLink()
	{
		if(mpPrevNode != NULL)
			mpPrevNode->NextLinkTo(mpNextNode) ;
		if(mpNextNode != NULL)
			mpNextNode->PrevLinkTo(mpPrevNode) ;
	}

	void CutOffLink()
	{
		mpPrevNode = NULL ;
		mpNextNode = NULL ;
	}

protected :
	CSafeLink *mpPrevNode ;
	CSafeLink *mpNextNode ;
} ;