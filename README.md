# Micro
 
## What is this?

Micro is a VR testbed that allowed me to explore how UE5 handles VR. Right now, it only has 1 loopable game, where you grab a handgun and shoot at oncoming missiles to defend a wall. There is also a lightsaber deflection test, but decided not to further develop for it as I wanted something more straightforward for others to play.

## Post Mortem

The only thing I would change differently was I would convert the GrabableComponent to a C++ SceneComponent instead of a Blueprint one, so that way I could attach the components and events at the C++ level instead of having to do some weird archetecture in Blueprint (this was due to the VR template only being available in Blueprint as of 1/16/23).

I think I'll port over Epics Blueprint focuses components to C++ components next time. 
