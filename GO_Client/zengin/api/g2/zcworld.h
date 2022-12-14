/* Gothic Online ZenGin research (based on g2ext) */



#ifndef __API_G2_ZCWORLD_H__
#define __API_G2_ZCWORLD_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

#include "api/g2/zcbsptree.h"

class zCVob;
class zCVertex;
class zCCSPlayer;
class zCWayNet;
class zCWorldPerFrameCallback;
class zCSkyControler;
class zCZone;
class zCSession;
class zCViewProgressBar;

#define zCWorld_DIMENSION 3
#define VOB_HASHTABLE_SIZE 2048

enum zTWorldLoadMode         
{   
	zWLD_LOAD_GAME_STARTUP,         
	zWLD_LOAD_GAME_SAVED_DYN,       
	zWLD_LOAD_GAME_SAVED_STAT,      
	zWLD_LOAD_EDITOR_COMPILED,      
	zWLD_LOAD_EDITOR_UNCOMPILED,    
	zWLD_LOAD_MERGE 
};

enum zTWorldSaveMode         
{   
	zWLD_SAVE_GAME_SAVED_DYN,       
	zWLD_SAVE_EDITOR_COMPILED,      
	zWLD_SAVE_EDITOR_UNCOMPILED,    
	zWLD_SAVE_COMPILED_ONLY         
};

enum zTWorldLoadMergeMode    
{   
	zWLD_LOAD_MERGE_ADD,                    
	zWLD_LOAD_MERGE_REPLACE_ROOT_VISUAL 
};

enum zTStaticWorldLightMode 
{   
	zWLD_LIGHT_VERTLIGHT_ONLY,
	zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_LOW_QUAL,
	zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_MID_QUAL,
	zWLD_LIGHT_VERTLIGHT_LIGHTMAPS_HI_QUAL
};

/** Insert description. */
class zCWorld : public zCObject
{
private:
	zCTree<zCVob>			globalVobTree;

	int						foundHit;
	zCVob*					foundVob;  
	zCPolygon*				foundPoly;
	zVEC3					foundIntersection;
	zVEC3					foundPolyNormal;   
	zCVertex*				foundVertex;
	zCSession*				ownerSession;
	zCCSPlayer*				csPlayer;

	zSTRING					m_strlevelName;              
	int						compiled;
	int						compiledEditorMode;
	int						traceRayIgnoreVobFlag;              
	int						m_bIsInventoryWorld;        
	zTWld_RenderMode		worldRenderMode;
	zCWayNet*				wayNet;
	zTFrameCtr				masterFrameCtr;        
	float					vobFarClipZ;              
	float					vobFarClipZScalability;
	
	zCArray<zCVob*>			traceRayVobList;
	zCArray<zCVob*>			traceRayTempIgnoreVobList;

	int						renderingFirstTime;
	int						showWaynet;       
	int						showTraceRayLines;        
	zCViewProgressBar*  	progressBar;
	DWORD					unarchiveFileLen;
	DWORD					unarchiveStartPosVobtree;
	int						numVobsInWorld;

	zCArray<zCWorldPerFrameCallback*> perFrameCallbackList;

	zCSkyControler*			skyControlerIndoor;
	zCSkyControler*			skyControlerOutdoor;
	zCSkyControler*			activeSkyControler;

	zCArray<zCZone*>		zoneGlobalList;
	zCArraySort<zCZone*>	zoneActiveList;
	zCArraySort<zCZone*>	zoneLastClassList;

	//zCVobBBox3DSorter<zCZone> zoneBoxSorter
	/*0x0118*/          int zoneBoxSorter_vtbl;     // Method table
	//zCArray<zTBoxSortHandle *>        handles;
	/*0x011C*/          int zoneBoxSorter_handles_array;         //zTBoxSortHandle**
	/*0x0120*/          int zoneBoxSorter_handles_numAlloc;      //int
	/*0x0124*/          int zoneBoxSorter_handles_numInArray;    //int
	//zCArraySort<zTNode*> nodeList[zCWorld_DIMENSION];
	//0
	/*0x0128*/          int zoneBoxSorter_nodeList0_array;         //zTNode**
	/*0x012C*/          int zoneBoxSorter_nodeList0_numAlloc;      //int             
	/*0x0130*/          int zoneBoxSorter_nodeList0_numInArray;    //int             
	/*0x0134*/          int zoneBoxSorter_nodeList0_compare;       //int    (*Compare)(const void* ele1,const void* ele2)
	//1                                                
	/*0x0138*/          int zoneBoxSorter_nodeList1_array;         //zTNode**
	/*0x013C*/          int zoneBoxSorter_nodeList1_numAlloc;      //int             
	/*0x0140*/          int zoneBoxSorter_nodeList1_numInArray;    //int             
	/*0x0144*/          int zoneBoxSorter_nodeList1_compare;       //int    (*Compare)(const void* ele1,const void* ele2)
	//2                                                
	/*0x0148*/          int zoneBoxSorter_nodeList2_array;         //zTNode**
	/*0x014C*/          int zoneBoxSorter_nodeList2_numAlloc;      //int             
	/*0x0150*/          int zoneBoxSorter_nodeList2_numInArray;    //int             
	/*0x0154*/          int zoneBoxSorter_nodeList2_compare;       //int    (*Compare)(const void* ele1,const void* ele2)
	/*0x0158*/          int zoneBoxSorter_sorted;                  //zBOOL

	//zCVobBBox3DSorter<zCZone>::zTBoxSortHandle    zoneActiveHandle;
	/*0x015C*/			int zoneActiveHandle_vtbl;                  //Pointer to method table
	/*0x0160*/			int zoneActiveHandle_mySorter;              //zCBBox3DSorterBase*
						zTBBox3D bbox3D;

	/*0x017C*/			int zoneActiveHandle_indexBegin [zCWorld_DIMENSION]; //int
	/*0x0188*/			int zoneActiveHandle_indexEnd   [zCWorld_DIMENSION]; //int

	//zCArray<VOB*> activeList;
	/*0x0194*/				int zoneActiveHandle_activeList_array;         //VOB **
	/*0x0198*/				int zoneActiveHandle_activeList_numAlloc;      //int             
	/*0x019C*/				int zoneActiveHandle_activeList_numInArray;    //int             

	int						addZonesToWorld;
	int						showZonesDebugInfo;

	zCCBspTree*				cbspTree;
	zCBspTree				bspTree;

	zCArray<zCVob*>			activeVobList;
	zCArray<zCVob*>			walkList;
	zCArray<zCVob*>			vobHashTable[VOB_HASHTABLE_SIZE];

	zSTRING					worldFilename;
	zSTRING					worldName;

	zCListSort<zCVob>*		voblist;
	zCListSort<oCNpc>*		voblist_npcs;
	zCListSort<oCItem>*		voblist_items;

public:
	zSTRING GetWorldName() {XCALL(0x00428B00);};
	//.text:00624810 ; public: class zCTree<class zCVob> * __thiscall zCWorld::AddVob(class zCVob *)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCTree<zCVob>* AddVob(zCVob* pA) 
	{ 
		XCALL(0x005F6340) 
	};

	zCArray<zCVob*> GetActiveVobList()
	{
		return (*(zCArray<zCVob*>*)((DWORD)this+0x0228));
	};

	zCTree<zCVob> GetGlobalVobTree()
	{
		return (*(zCTree<zCVob>*)((DWORD)this+0x0024));
	};

	//.text:007800C0 ; public: virtual void __thiscall oCWorld::RemoveVob(class zCVob *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void RemoveVob(zCVob* pA) 
	{ 
		XCALL(0x005F66C0) 
	};

	//.text:007806C0 ; public: virtual void __thiscall oCWorld::SearchVobListByName(class zSTRING const &, class zCArray<class zCVob *> &)
	/** Insert description.
	* @usable Ingame only.
	*/
	void SearchVobListByName(const zSTRING& name, zCArray<zCVob*>& resultList)
	{
		XCALL(0x005F5B60);
	};

	/** Insert description.
	* @usable Ingame only.
	*/
	zCListSort<zCVob>* GetVobList(void)
	{
		return (*(zCListSort<zCVob>**)((DWORD)this+0x6258));
	};

	/** Insert description.
	* @usable Ingame only.
	*/
	zCListSort<oCNpc>* GetNpcList(void)
	{
		return this->voblist_npcs;
	};

	/** Insert description.
	* @usable Ingame only.
	*/
	zCListSort<oCItem>* GetItemList(void)
	{
		return this->voblist_items;
	};

	/** Insert description.
	* @usable Ingame only.
	*/
	zCSkyControler* GetIndoorSkyController(void)
	{
		return this->skyControlerIndoor;
	};

	/** Insert description.
	* @usable Ingame only.
	*/
	zCSkyControler* GetOutdoorSkyController(void)
	{
		return this->skyControlerOutdoor;
	};

	/** Insert description.
	* @usable Ingame only.
	*/
	zCSkyControler* GetActiveSkyController(void)
	{
		return this->activeSkyControler;
	};
};

#undef __G2EXT_API_HEADER

#endif // __API_G2_ZCWORLD_H__