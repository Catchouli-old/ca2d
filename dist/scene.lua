function loadscene(scene)

	for entkey, entity in pairs(scene["entities"]) do
			
		local e = game:createEntity()
	
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
			Position(math.random() * 2 - 1, math.random() * 2 - 1),
			Velocity(math.random() * 5 - 2.5, math.random() * 5 - 2.5),
			Radius(math.random() * 0.3),
			Color(math.random(), math.random(), math.random()),
		},
	
		mousecircle =
		{
			CircleRenderer(),
			CircleCollider(),
			Position(math.random() * 2 - 1, math.random() * 2 - 1),
			Velocity(math.random() * 5 - 2.5, math.random() * 5 - 2.5),
			Radius(math.random() * 0.3),
			Color(math.random(), math.random(), math.random()),
			MouseFollow(),
		},
		
	}
}

loadscene(scene)