math.randomseed(os.time())

function loadscene(scene)

	for entkey, entity in pairs(scene["entities"]) do
			
		local e = world:createEntity()
	
		for compkey, component in pairs(entity) do
		
			e:addComponent(component)
		
		end
		
		_G[entkey] = e
	
	end

end

scene =
{
	entities =
	{
	
		circle =
		{
			CircleRenderer(),
			CircleCollider(),
			Position(math.random(800), math.random(800)),
			Velocity(math.random(500), math.random(500)),
			Radius(math.random() * 50),
			Color(math.random(), math.random(), math.random()),
		},
		
	}
}

loadscene(scene)