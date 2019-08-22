// ListContour.h: interface for the CListContour class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCONTOUR_H__84C3BBC0_6F70_416A_8194_9657813FF3AE__INCLUDED_)
#define AFX_LISTCONTOUR_H__84C3BBC0_6F70_416A_8194_9657813FF3AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>

#include "Contour.h"

namespace Jonathan
{

// a list of point index referring to the secondary grid
// Let i the index of a point,
typedef std::list<unsigned int> CLineStrip;
typedef std::list<CLineStrip *> CLineStripList;
typedef std::vector<CLineStripList> CLineStripListVector;

class CListContour : public CContour
{
public:
	CListContour();
	virtual ~CListContour();

	// retreiving list of line strip for the i-th contour
	CLineStripList *GetLines(unsigned int iPlane)
	{
		if (iPlane < 0 || iPlane >= GetNPlanes())
			return nullptr;
		return &m_vStripLists[iPlane];
	};

	// Initializing memory
	virtual void InitMemory();
	// Cleaning memory and line strips
	virtual void CleanMemory();
	// Generate contour strips
	virtual void Generate();

	// Adding segment to line strips
	// See CContour::ExportLine for further details
	void ExportLine(int iPlane, int x1, int y1, int x2, int y2);

	// Basic algorithm to concatanate line strip. Not optimized at all !
	void CompactStrips();
	/// debuggin
	void DumpPlane(unsigned int iPlane) const;

	// Area given by this function can be positive or negative depending on the winding direction of the contour.
	double Area(CLineStrip *Line);

	double EdgeWeight(CLineStrip *pLine, double R);
	bool PrintContour(char *fname);

protected:
	// Merges pStrip1 with pStrip2 if they have a common end point
	bool MergeStrips(CLineStrip *pStrip1, CLineStrip *pStrip2);
	// Merges the two strips with a welding threshold.
	bool ForceMerge(CLineStrip *pStrip1, CLineStrip *pStrip2);
	// returns true if contour is touching boundary
	bool OnBoundary(CLineStrip *pStrip);

private:
	// array of line strips
	CLineStripListVector m_vStripLists;
};

} // namespace Jonathan

#endif // !defined(AFX_LISTCONTOUR_H__84C3BBC0_6F70_416A_8194_9657813FF3AE__INCLUDED_)
