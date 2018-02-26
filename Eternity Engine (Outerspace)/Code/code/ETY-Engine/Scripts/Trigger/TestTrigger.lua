--[Events]
function Events()

	--c_etyTrigger:add_UnitEvent( 0, "Player", true);
	c_etyTrigger:add_TimeEvent( 0, 5.0, true);
	
end
--[Events]

--[Actions]
function Actions()

	print("Moin");
	
end
--[Actions]

--[Conditions]
function Conditions()

	testEntity 				= c_etyEntitymanager:get_Entity("Player");
	testAttributeComponent 	= testEntity:get_AttributeComponent("AttributeComponent");
	testAttributes			= testAttributeComponent.m_c_etyAttributes;
	testAttributes			= testAttributeComponent.m_c_etyAttributes;	
	
	if c_etyEntitymanager:get_Entity("Player")
	:has_Component("RenderComponent") == true 
	and testAttributes:get_UnsignedIntAttribute("uiStructureStability") < 0  then
		Actions()
		return true;
	else
		print("fuck");
		return false;
	end
	
end
--[Conditions]

