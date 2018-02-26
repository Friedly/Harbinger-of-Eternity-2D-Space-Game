--[Events]
function Events()
	c_etyTrigger:add_TimeEvent( 0, 1.0, true);
end
--[Events]

--[Actions]
function Actions()

	c_sfVector2fTopLeft 	= sfVector2f( 2000, 1300 );
	c_sfVector2fTopRight 	= sfVector2f( 2400, 1300 );
	c_sfVector2fBottomRight = sfVector2f( 2400, 1700 );
	c_sfVector2fBottomLeft 	= sfVector2f( 2000, 1700 );
	
	testMovableNPCComponent1 					= 	c_etyEntitymanager:get_Entity("testNPCEntity1"):get_MoveableNPCComponent("MovableComponent");
	testMovableNPCComponent2 					= 	c_etyEntitymanager:get_Entity("testNPCEntity2"):get_MoveableNPCComponent("MovableComponent");
	testMovableNPCComponent3 					= 	c_etyEntitymanager:get_Entity("testNPCEntity3"):get_MoveableNPCComponent("MovableComponent");
	testMovableNPCComponent4 					= 	c_etyEntitymanager:get_Entity("testNPCEntity4"):get_MoveableNPCComponent("MovableComponent");
	
	testMovableNPCComponent1:add_PatrolPoint(c_sfVector2fTopLeft);
	testMovableNPCComponent1:add_PatrolPoint(c_sfVector2fTopRight);
	testMovableNPCComponent1:add_PatrolPoint(c_sfVector2fBottomRight);
	testMovableNPCComponent1:add_PatrolPoint(c_sfVector2fBottomLeft);
	
	
	testMovableNPCComponent2:add_PatrolPoint(c_sfVector2fTopRight);
	testMovableNPCComponent2:add_PatrolPoint(c_sfVector2fBottomRight);
	testMovableNPCComponent2:add_PatrolPoint(c_sfVector2fBottomLeft);
	testMovableNPCComponent2:add_PatrolPoint(c_sfVector2fTopLeft);
	
	testMovableNPCComponent3:add_PatrolPoint(c_sfVector2fBottomRight);
	testMovableNPCComponent3:add_PatrolPoint(c_sfVector2fBottomLeft);
	testMovableNPCComponent3:add_PatrolPoint(c_sfVector2fTopLeft);
	testMovableNPCComponent3:add_PatrolPoint(c_sfVector2fTopRight);
	
	testMovableNPCComponent4:add_PatrolPoint(c_sfVector2fBottomLeft);
	testMovableNPCComponent4:add_PatrolPoint(c_sfVector2fTopLeft);
	testMovableNPCComponent4:add_PatrolPoint(c_sfVector2fTopRight);
	testMovableNPCComponent4:add_PatrolPoint(c_sfVector2fBottomRight);
	
	testMovableNPCComponent1:set_PatrolModus(true);
	testMovableNPCComponent2:set_PatrolModus(true);
	testMovableNPCComponent3:set_PatrolModus(true);
	testMovableNPCComponent4:set_PatrolModus(true);
	
end
--[Actions]

--[Conditions]
function Conditions()
	if true then
		Actions()
		return true;
	else
		return false;
	end
end
--[Conditions]

