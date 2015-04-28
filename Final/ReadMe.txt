wasd to move the camera and clicking to move around the game

camera works nicelyish and works no matter what.

This is because there is an update and a private update.

So far CollisionData and CollisionDetector hold all of the collision info,
but there is no check so far.

Rigid body has the gravity generator and proper update function.

Lots of variety of collision info.

Spheres currently render because in order to get a cube to have a texture and work I would need
to create a way to create cubes. The basics only allow spheres to be nice and easy to use.

Resolver starts to work however
int i;
+	m_iterationsUsed = 0;
+
+	while (m_iterationsUsed < m_iterations)
+	{
+		int max = 50;
+		int maxIndex = numContacts;
+		for (i = 0; i < numContacts; i++)
+		{
+			float sepVel = contactArray[i].calculateSeparatingVelocity();
+			if (sepVel < max && contactArray[i].penetration > 0)
+			{
+				max = sepVel;
+				maxIndex = i;
+			}
+		}
+
+		if (maxIndex == numContacts) break;
+
+		contactArray[maxIndex].resolve(duration);
+		m_iterationsUsed++;
+	}

proper resolve attempt now how I actually did it because it caused things to fall through ground

Everytime you click and lose mouse the next time you click it re-centers your mouse

The release folder does not work because SOIL can't be used in release currently