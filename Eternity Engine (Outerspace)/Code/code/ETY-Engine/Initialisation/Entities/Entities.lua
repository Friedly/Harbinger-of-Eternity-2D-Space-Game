-- enLASERWEAPON, enROCKETLAUNCHER, enPROJECTILEWEAPON, enENGINE, enGENERATOR, enSHIELD, enARMOR, enAMMUNITIONDUMP, enFREE
--	0					1					2				3			4			5		6		7					8

function AlienCarrier()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
		
	end
	
end

function AlienCruiser()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
		
	end
	
end

function AlienFighter()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
		
	end
	
end

function AlienScorpion()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
	
	end
	
end

function HumanCarrier()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
	
	end
	
end

function HumanCruiser()

	if c_etyItemModulesComponent ~= nil then

		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );

		c_etyItemModulesComponent:create_WeaponModule( "LEFT" , sfVector2f( 0, 0 ), sfVector2i( 1, 1 ), 2 );
		c_etyItemModulesComponent:create_WeaponModule( "RIGHT", sfVector2f( 0, 0 ), sfVector2i( 1, 1 ), 2 );
		
	end
	
end

function HumanFighter()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
		
		c_etyItemModulesComponent:create_WeaponModule( "LEFT" , sfVector2f( 26, 53 ), sfVector2i( 1, 1 ), 2 );
		--c_etyItemModulesComponent:create_WeaponModule( "RIGHT", sfVector2f( 64, 53 ), sfVector2i( 1, 1 ), 2 );
	
	end
	
end

function HumanPhalanx()

	if c_etyItemModulesComponent ~= nil then

		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );

	end
	
end

function HumanSpacestation()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
	
	end
	
end

function HumanDrone()

	if c_etyItemModulesComponent ~= nil then

		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );

	end
	
end

function HumanDrone2()

	if c_etyItemModulesComponent ~= nil then
	
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 3 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 4 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 5 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 6 );
		c_etyItemModulesComponent:create_EquipmentModule( sfVector2i( 1, 1 ), 7 );
	
	end
	
end