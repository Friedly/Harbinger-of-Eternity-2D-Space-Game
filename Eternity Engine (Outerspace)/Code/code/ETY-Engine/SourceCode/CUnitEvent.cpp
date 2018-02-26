#include "CUnitEvent.hpp"
#include "CTrigger.hpp"
#include "CEntity.hpp"
#include "CAttributeComponent.hpp"
#include "CWorld.hpp"


														ety::CUnitEvent::CUnitEvent				( void )
														:m_strEntityID							( "" )
														,m_bSpecificUnitEvent					( false )
														,mp_c_etyEntityTriggeringUnit			( NULL )
{
}

	
														ety::CUnitEvent::~CUnitEvent			( void )
{
}


														ety::CUnitEvent::CUnitEvent				( enum UnitEventType::en_etyUnitEventType en_etyUnitEventType, std::string strEntityID, 
																									bool bActive, CTrigger* p_c_etyTriggerParent )
														:m_strEntityID							( strEntityID )
														,m_bSpecificUnitEvent					( true )
														,mp_c_etyEntityTriggeringUnit			( NULL )
														,m_en_etyUnitEventType					( en_etyUnitEventType )
{
	m_bActive					=	bActive;
	mp_c_etyTriggerParent		=	p_c_etyTriggerParent;
	m_en_etyTriggerEventType	=	TriggerEventType::enUNITEVENT;

	if(strEntityID == "")
	{
		m_bSpecificUnitEvent = false;
	}
}
	

bool													ety::CUnitEvent::update_Event			( const sf::Uint32& uiFrameTime )
{
	mp_c_etyEntityTriggeringUnit	=	NULL;

	if(m_en_etyUnitEventType == UnitEventType::enDIES)
	{
		if(m_bSpecificUnitEvent == true)
		{
		}
		else
		{
		}
	}
	else if(m_en_etyUnitEventType == UnitEventType::enNOTICESENEMYINRANGE)
	{
		if(m_bSpecificUnitEvent == true)
		{
			CEntity* p_c_etyEntityTriggerUnit	=	gp_c_etyWorld->get_Entitymanager()->get_Entity(m_strEntityID);
			mp_c_etyEntityTriggeringUnit		=	p_c_etyEntityTriggerUnit;

			if(m_strEntityID != "Player")
			{
				CEntity* p_c_etyEntityPlayer	=	gp_c_etyWorld->get_Entitymanager()->get_Entity("Player");


				ety::CRenderComponent* p_c_etyRenderComponentTriggerUnit	=	p_c_etyEntityTriggerUnit->get_Component<ety::CRenderComponent>("RenderComponent");
				ety::CRenderComponent* p_c_etyRenderComponentPlayer			=	p_c_etyEntityPlayer->get_Component<ety::CRenderComponent>("RenderComponent");

				if(p_c_etyRenderComponentTriggerUnit == NULL || p_c_etyRenderComponentPlayer == NULL)
				{
					return false;
				}

				float fDistance		=	ety::CMath::calculate_Length<float>(
											ety::CMath::build_DirectionVector<float>(p_c_etyRenderComponentTriggerUnit->get_Position(), p_c_etyRenderComponentPlayer->get_Position()));

				if(fDistance <= p_c_etyEntityTriggerUnit->get_Component<ety::CMovableNPCComponent>("MovableComponent")->get_DetectionRadius())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
		}
	}
	
	
	
	/*std::vector<ety::CEntity*>::iterator	itEntities	=	m_vectorEntityIDs.begin();
	std::vector<enum ety::UnitEventType::en_etyUnitEventType>	m_vectorUnitEvents;
	std::vector<enum ety::UnitEventType::en_etyUnitEventType>::iterator	itUnitEvents;

	for(itEntities ; itEntities != m_vectorEntityIDs.end() ; itEntities++)
	{
		if(m_en_etyUnitEventType == UnitEventType::enDIES)
		{
			if(*(*itEntities)->get_Component<ety::CAttributeComponent>("AttributeComponent")->m_c_etyAttributes.get_Attribute<unsigned int>("uiStructureStability") <= 0.f)
			{
				return true;
			}
		}
		else if(m_en_etyUnitEventType == UnitEventType::enNOTICESENEMYINRANGE)
		{
			if(m_bSpecificUnitEvent == true)
			{
				if()
				{

				}
			}
		}
	*/

	return false;
}

										
const	bool&											ety::CUnitEvent::get_SpecificUnitEvent	( void )
{
	return m_bSpecificUnitEvent;
}
const	enum ety::UnitEventType::en_etyUnitEventType&	ety::CUnitEvent::get_UnitEventType		( void )
{
	return m_en_etyUnitEventType;
}
		ety::CEntity*	const							ety::CUnitEvent::get_TriggeringUnit		( void )
		{
			return	mp_c_etyEntityTriggeringUnit;
		}