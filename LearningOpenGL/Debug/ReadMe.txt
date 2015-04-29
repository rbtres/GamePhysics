Tried to get the best positioning as possible to see the launch.
I used similar box-sphere and sphere-sphere same as the rigid simulation.

Took out all camera controls atm in the build you can put them back by doing
	glLoadIdentity();
	glRotatef(m_rot.X, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
	glRotatef(m_rot.Y, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
	glTranslated(-m_pos.X, -m_pos.Y, -m_pos.Z);
in the InputManager update class. It is currently hard coded numbers
GitHub location: https://github.com/rbtres/GamePhysics/tree/master/LearningOpenGL

Known problems, I have the bouncyness really high so there seems to be energy gained on collisions similarly to a lot of
balls at once. It can jump through some object if its velocity is too high missed timestep.

Project1.exe is the exe and you will get to watch it play. It works nicely.

Sometimes It has to be ran twice.
I fixed some collision problems in my logic since last attempt