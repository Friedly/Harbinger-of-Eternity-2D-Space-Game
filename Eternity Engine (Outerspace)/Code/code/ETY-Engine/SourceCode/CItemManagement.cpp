#include "CItemManagement.hpp"

#include "CRessourceManager.hpp"
#include "CIniFile.hpp"

#include "CAmmunitionDump.hpp"
#include "CArmor.hpp"
#include "CLaserWeapon.hpp"
#include "CProjectileWeapon.hpp"
#include "CShield.hpp"
#include "CEngine.hpp"
#include "CRocketLauncher.hpp"
#include "CGenerator.hpp"

										ety::CItemManagement::CItemManagement		( void )
										{
										}
										ety::CItemManagement::~CItemManagement		( void )
										{
											clear_Items();
										}

void									ety::CItemManagement::clear_Items			( void )
										{
											for( std::map<unsigned int, mapItemsByType>::iterator itItemTypebByClass = m_stdMapItemTypebByClass.begin(); itItemTypebByClass != m_stdMapItemTypebByClass.end(); itItemTypebByClass++ )
											{
												for( mapItemsByType::iterator itItemByType = itItemTypebByClass->second.begin(); itItemByType != itItemTypebByClass->second.end(); itItemByType++ )
												{
													for( unsigned int uiItemIndex = 0; uiItemIndex < itItemByType->second.size(); uiItemIndex++ )
													{
														if( itItemByType->second[uiItemIndex] != NULL )
														{
															delete itItemByType->second[uiItemIndex];
															itItemByType->second[uiItemIndex] = NULL;
														}
													}

													itItemByType->second.clear();
												}
											}

											m_stdMapItemTypebByClass.clear();
										}

void									ety::CItemManagement::load_Items			( const std::string& strDirectory, const ety::ModuleType::en_etyModuleType en_etyModuleType, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
										{
											ety::CIniFile c_etyIniFile;

											c_etyIniFile.set_IniFileDirectory( strDirectory );

											std::vector<std::string> c_stdVectorItems = c_etyIniFile.read_Sections();

											for( unsigned int iIndexOfItem = 0; iIndexOfItem < c_stdVectorItems.size(); ++iIndexOfItem )
											{
												std::map<std::string, CItem*>::iterator itItemByName = m_stdMapItemByName.find( c_stdVectorItems[iIndexOfItem] );

												if( itItemByName != m_stdMapItemByName.end() )
												{
													continue;
												}
												else
												{
													ety::CItem* p_c_NewItem = NULL;

													switch( en_etyModuleType )
													{
													case ety::ModuleType::enAMMUNITIONDUMP	:

														p_c_NewItem = new ety::CAmmunitionDump		( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enARMOR			:

														p_c_NewItem = new ety::CArmor				( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enENGINE			:

														p_c_NewItem = new ety::CEngine				( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enGENERATOR		:

														p_c_NewItem = new ety::CGenerator			( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enLASERWEAPON		:

														p_c_NewItem = new ety::CLaserWeapon			( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enPROJECTILEWEAPON	:

														p_c_NewItem = new ety::CProjectileWeapon	( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enROCKETLAUNCHER	:

														p_c_NewItem = new ety::CRocketLauncher		( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;

													case ety::ModuleType::enSHIELD			:

														p_c_NewItem = new ety::CShield				( strDirectory, c_stdVectorItems[iIndexOfItem], p_c_etyCurrentRessourceManager );

														break;
													}

													if( p_c_NewItem != NULL )
													{
														std::map< unsigned int, mapItemsByType >::iterator itItemTypeByClass = m_stdMapItemTypebByClass.find( p_c_NewItem->get_Class() );
			
														if( itItemTypeByClass != m_stdMapItemTypebByClass.end() )
														{
															mapItemsByType::iterator itItemByType = m_stdMapItemTypebByClass[p_c_NewItem->get_Class()].find( en_etyModuleType );

															if( itItemByType != m_stdMapItemTypebByClass[p_c_NewItem->get_Class()].end() )
															{
																itItemByType->second.push_back( p_c_NewItem );
															}
															else
															{
																itItemTypeByClass->second[en_etyModuleType].push_back( p_c_NewItem );
															}
														}
														else
														{
															m_stdMapItemTypebByClass[p_c_NewItem->get_Class()][en_etyModuleType].push_back( p_c_NewItem );
														}

														m_stdMapItemByName[c_stdVectorItems[iIndexOfItem]] = p_c_NewItem;
													}
												}
											}
										}

ety::CItem*					const		ety::CItemManagement::get_Item				( const std::string& c_stdStringItemID )
{
	std::map<std::string, CItem*>::iterator itItemByName = m_stdMapItemByName.find( c_stdStringItemID );

	if( itItemByName != m_stdMapItemByName.end() )
	{
		return itItemByName->second;
	}

	return NULL;
}
std::vector<ety::CItem*>*	const		ety::CItemManagement::get_Items				( const unsigned int uiClass, const ety::ModuleType::en_etyModuleType en_etyModuleType )
{
	return &m_stdMapItemTypebByClass[uiClass][en_etyModuleType];
}