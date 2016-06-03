*Warning:* This code is REALLY old, not really commented (and the comments added are in Swedish) and .. yeah that's it.

---

# What is this?

This is an implementation of [Verlet itegration](https://en.wikipedia.org/wiki/Verlet_integration) to achieve a nice cloth simulation with tearing as well. You can see it in action here: https://www.youtube.com/watch?v=G05M_Y6NQVM

# Issues you will face if you try to run it

- You need Allegro
- You need to create your own project (I only had an old one for VS and I no longer user Windows)
- Probably some more when you build it

# Code overview

- Everything is seemingly implemented in the .h files. I don't remember why.  
- **Jvector2.h** is a 2D vector with some helper methods.
- **JVerletPoint.h** is simply a verlet point. Read the wiki to know about it.
- **JVerletConstraint.h** is the constraints between verlet points that keeps them together. It includes some different versions. **JVerletFixedLengthConstraint** should not allow for any elasticity, but actually looking at the code it seems like it can have that, oops. **JVerletTearConstraint** will remove one of its verlet points if the distance between them is too far, I think. This is used to make the tearing of the cloth later. **JVerletFixedPositionConstraint** is a constraints applied to ONE verlet point. You can apply this to make a point fixed in its position forever.
- **Example_Verlet_Softbody.h** and **Example_Verlet_Cloth.h** are sort of a "scenarios" where it only is used to setup a bunch of verlet points and constraints into nice visual examples.
- **Main.cpp** contains a bunch of helper methods for making strings from various types, I think it is used to display coordinates and so on on the screen. It also contains helper methods for drawing stuff on the screen, like dots and lines (linje = line in swedish). It then sets up allegro and creates the window and the "Example_x_xx" mentioned above and kicks off everything with a runloop. You can uncomment the stuff in the while loop to switch between the two examples.

# Help

Feel free to ask me for help about stuff (email is in profile)

# License

If you use this code to make some new AAA title I will expect 10% of your profits.
