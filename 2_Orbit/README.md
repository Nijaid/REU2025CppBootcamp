# 2_Orbit

This is a small C++ project that calculates the evolution of a binary system in Newtonian gravity. Poke around the code, and see the slides to understand its structure.

## Requirements
 To compile, we configure the build with CMake. [CMake](https://cmake.org/cmake/help/latest/) is a wonderful tool that manages the building of source code; you can find an introduction in the link. It generates Makefiles - instructions for compiling and installing and more - based on your hardware and other options that you may give the configuration. This allows for code to be portable across different systems. You should be able to install it using your favorite package manager. We will need at least version 4.0; most likely a newer version will be installed but that is not a problem.

 ## Generating the configuration
 We will not be going into the details of CMake, but you can take a look at the root [CMakeLists.txt](CMakeLists.txt) and its comments. To generate the configuration, first create a build directory and change your working directory to it,
 ```shell
 mkdir build
 cd build
 ```
 All of CMake's intermediate output will be placed in here, so if something goes wrong, it can just be deleted with `rm -rf *` and ran again.

 To generate, run
 ```shell
 cmake \
 -DCMAKE_BUILD_TYPE=Release \
 -DCMAKE_INSTALL_PREFIX=../ \
 -DCMAKE_BUILD_WITH_INSTALL_RPATH=True \
 ../
 ```
 The `-D` are options for the configuration; `CMAKE_BUILD_TYPE` determines some compilation options, such as the optimization, and `CMAKE_INSTALL_PREFIX` determines where the `install` targets will be placed. The install location is simply the root directory of the project, and is _not_ where things should be placed if they are to be used by other codes. (The common location is `/usr/local` although that may be different for M-chip Macs.) As the root directory is not a place expected for libraries to be installed (which is what our configuration will do), we specify with `CMAKE_BUILD_WITH_INSTALL_RPATH` that we want our install location to be used to link to the library (look inside the CMakeLists.txt for this option). The final argument is `../` which tells `cmake` where to look for the root CMakeLists.txt.

 ## Compiling and Installing
 If successful, `cmake` will have produced another copy of the source directory with the files it needs to compile the project. There should now be a `Makefile` in the current directory, and can be run with
 ```shell
 make
 ```
 If successful, all the necessary binaries have been compiled. We can now "install" the library that solves for orbits, `orbitsolver`, and an executable that uses it, `orbitExample`; `cmake`'s standard output will tell where they are. The installation is done with
 ```shell
 make install
 ```
 These are the usual steps for CMake projects. They are pretty straightforward for the user, and is why many developers have adopted CMake to distribute their code.

 ## Code development
 The beauty of these Makefiles is that they keep track of how files depend on each other. When changes are made to a file, `make` know what files depend on it so that they are also re-compiled, while leaving other files alone. New files have to be added to the CMakeLists, which then have to be re-configured, in order for this to work.


## Execution

The project should have installed in the `bin` directory, where you should find the executable `orbitExample`. This is set up to integrate the evolution of the orbital phase $\phi(t)$ (see the [section below](#the-two-body-problem)) for the Sun-Earth system; take a look at its source file in the `app` directory. Its usage is, if you're in `bin`
```shell
./orbitExample NAME
```
where `NAME` will be used to name the output data file.
This output is a simple text file with a header and two columns: time $t$ and $\phi(t)$. You can see what the first ten lines of it look like by running `head NAME`.

### Visualization

If you have `Python`, `numpy`, and `matplotlib`, then you can run a Python script set up in the `python` directory that can make a quick plot. With it as the working directory, one can run
```shell
python plot_orbit.py ../bin/NAME
```
and a figure will open up.

## Going Beyond

It may have been a lot of information, but it can be learned and absorbed over time as you revisit and study it on your own. Here are some things to make you think about improvements that could be done:
- The output so far is only for $\phi(t)$. How would you obtain the evolution of the separation vector?
- The integration method implemented is only one of several. Are there better alternatives? The Newtonian problem is conservative; there are integration methods designed for such problems, but are not implemented in GSL. Maybe you can write your own!


# The Two-Body Problem
This is one of the physics problems of all time; it is well-understood theoretically and has been investigated empirically for centuries. Most physics undergrads will have studied it in their mechanics courses by their third year, but we will give a little preview here to bring us up to speed. Empirically, massive bodies are seen to exert an influence over each other; this can be understood as the **gravitational force**, and can be understood within the framework established by Isaac Newtonian and his contemporaries.

Below we will review the Newtonian model of gravity and identify how we use it to understand the motion of two bodies influenced by their respective gravity. Our objective is to *determine* their motion. You might already be picturing plotting out their motion in space, such as on a Cartesian grid where the bodies move over time. But let's be careful to understand what "results" we'll be looking for. Do we want (x,y,z)-coordinates over time? Or are there other, more useful coordinates? To decide, let's first understand our model.

## Theoretical Overview
_Adapted from Section 3.2 of_ Gravity *by Poisson and Will, Cambridge University Press.*

The Newtonian model of gravity states that a body of inertial mass $m_{1}$ exerts a gravitational force $\vec{F}_{\rm g}$ on a body of mass $m_2$,
$$
\vec{F}_{\rm g} = -\frac{G m_1 m_2}{r^2} \hat{r},
$$
where $G$ is the gravitational constant, $r$ the distance between the bodies, and $\hat{r} \equiv \vec{r}/|\vec{r}|$ the unit vector from body 2 to body 1; that is, if the position of the $i$th body is $\vec{r}_i$, then $\vec{r}=\vec{r}_1 - \vec{r}_2$ is their *relative separation*. Body 2 also exerts the same force on 1, just in the opposite direction. A *center of mass* (also known as the barycenter) can then be defined between the bodies,
$$
\vec{R} = \frac{m_1}{m} \vec{r}_1 + \frac{m_2}{m} \vec{r}_2,
$$
where $m=m_1+m_2$ is the total mass. From Newton's second law it can be shown that $d^2\vec{R}/dt^2=0$, so we can set $\vec{R}=0$ as the origin. Together, the definitions of the relative separation and the center of mass, along with Newton's second law, give the *relative acceleration*,
$$
\ddot{\vec{r}} = -\frac{Gm}{r^2} \hat{r}.
$$

The two-body problem has now been reduced to an effective one-body problem.

Let's refresh on where we want to be. We want a description of the motion of the two bodies; in terms of the relative separation, they are found from the above to be
$$
\vec{r}_{1} = \frac{m_{2}}{m}\vec{r}, \quad \vec{r}_{2} = -\frac{m_{1}}{m}\vec{r}.
$$
To obtain the values of these vectors, we then have to solve the differential equation for $\vec{r}$. In principle one could then solve for the Cartesian components of $\vec{r}$. Certain simplifications happen, however, if we use coordinates that better represent the symmetries of our problem. First, we notice that the acceleration is purely along the separation vector. This implies that the motion of the two bodies is constrained to a 2D plane of the 3D space we started with, and that it does not change over time. Setting up coordinates that reflect this, we have two polar basis vectors on the plane,
$$
\hat{n} = [\cos\phi, \sin \phi, 0], \quad \hat{\lambda} = [-\sin \phi,\cos \phi,0],
$$
and a unit vector perpendicular to the plane, $\hat{z}$. We now have two degrees of freedom, $r$ and $\phi$, and can write the separation vector as $\vec{r} = r \hat{n}$. Noting that
$$
\frac{{d\hat{n}}}{d\phi} = \hat{\lambda}, \quad \frac{{d \hat{\lambda}}}{d\phi} = -\hat{n},
$$
we can write the time derivatives of $\vec{r}$ in terms of time derivatives of $r$ and $\phi$. The relative acceleration becomes
$$
\ddot{\vec{r}} = (\ddot{r}-r\dot{\phi}^2) \hat{n} + \frac{1}{r} \frac{d}{dt} (r^2 \dot{\phi}) \hat{\lambda}.
$$
We can match it to $-Gm/r^2\, \hat{r}$ to obtain the equations of motion (EOM). The symmetry we noticed earlier now appears explicitly: $r^2 \dot{\phi}$ is the $z$-component of the (reduced) angular momentum vector $\vec{l}=\vec{r}\times \vec{v}$ and from the EOM is seen to be *conserved*, that is, is a constant in time. This constant $l$ can be substituted into the radial equation to give
$$
\ddot{r} - \frac{l^2}{r^3} = - \frac{Gm}{r^2}.
$$
Along with $\dot{\phi}=l/r^2$, we now have the necessary equations of motion. We could try implementing these into an IVP solver, but it turns out the radial equation can be solved in terms of $\phi$:
$$
r(\phi) = \frac{p}{1+e \cos(\phi-\omega)}.
$$
Here, $e$ and $\omega$ are constants of integration known respectively as the **eccentricity** and the **longitude of pericenter**, and $p \equiv l^2/(Gm)$ is known as the **semi-latus rectum**. All of these names allude to the fact that $r(\phi)$ describes a conic section, specifically an ellipse when $0\leq e<1$, as is the case for *bound orbits*. We note that the motion has a period in $\phi$ ($\Delta \phi=2\pi$). Using this conic solution, we can substitute it into $\dot{\phi}$ to obtain
$$
\dot{\phi} = \sqrt{ \frac{Gm}{p^3} } (1 + e \cos(\phi-\omega))^2.
$$
Let us now see how we can solve this equation.

## The Initial-Value Problem
The equations that we want to solve are
$$
\begin{align} \\
\dot{\phi} &= \sqrt{ \frac{Gm}{p^3} } (1 + e \cos(\phi-\omega))^2, \\
r(\phi) &= \frac{p}{1+e \cos(\phi-\omega)}.
\end{align}
$$
In general, we cannot write down an equation $r(t)$ or $\phi(t)$ unless $e=0$; in this case then, $\dot{\phi}$ is constant and $r=p$ simply describes a circle. There are ways to solve for the motion approximately through an algebraic relation instead of through a differential equation (look up "Kepler's equation"), but that is not the purpose of this exercise. We want to solve this as an *initial-value problem* (IVP): given $N$ differential equations, if we have $N$ initial values for them, then it can be solved with generic algorithms. The C library `gsl` implements such algorithms, and so we will use it.

Let's see if our equations are a suitable IVP. There are a couple of parameters: that define our system. The main one is the total mass $m$, and the other is the semi-latus rectum $p=l^2/(Gm)$. For the latter, we will use a more practical definition in terms of the semi-major axis $a$, which is well-known for astrophysical systems:
$$ p = a(1-e^2). $$
We note we can find the **period** $P$ of the orbit by integrating $\dot{\phi}$ from $\phi(t=0)=0$ to $\phi(t=P)=2\pi$,
$$
P = 2\pi \sqrt{ \frac{a^3}{Gm} }.
$$
We can define all the constants we need now, given a binary of total mass $m$, semi-major axis $a$, eccentricity $e$, and longitude $\omega$, which are observable in practice. We note that $\omega$ is just the rotation off the $\phi=0$ axis, and when $\phi=\omega$, the binary is at its minimum separation, or *pericenter*. Knowing values for these (such as can be found for the solar system in [NASA's Planet Fact Sheets](https://nssdc.gsfc.nasa.gov/planetary/planetfact.html)) allows us then to solve for $r(t)$ and $\phi(t)$ as an IVP; that is we can find the values of $r$ and $\phi$ at specific points in $t$ that we'd like.

### Solving IVPs Numerically
To solve our IVP, we will use a common class of methods known as the *explicit Runge-Kutta* methods. The Runge-Kutta (RK) methods essentially uses the Taylor series of the function you are trying find to approximate its value at a time $t_n$ by using points between the initial $t_0$ and $t_n$. We won't go into detail here but the web offers many descriptions of these methods, such as can be found on [Wikipedia](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods).

This section is not about the origin of these methods, but rather how to *use* these methods. Numerical methods work on taking *steps* from $t_0$ to $t_n$, and some, like the one we will use, try to adapt the step size to obtain good accuracy in the solution, which is measured as something related to the difference in that solution between taking a step of certain size and then taking more steps of a smaller size; if the difference is smaller than some threshold, then it is considered accurate and the method stops shrinking the step size. But how to choose this step size? How to choose the accuracy? The latter question is usually figured out by trial and error, but the first is one we can attempt to clarify.

Take a look again at our equations. We are trying to find $\phi$ at times $t \in [t_{0},t_{n}]$; the step size must then be a fraction of $t_n - t_0$. But how small? A way to start this is by analyzing the units of our equations. $r$ has units of length, while $\phi$ is in radians (and in a period only changes by $2\pi$). We can thus try to get rid of these units and make our equations dimension-less. Radians are in a way not really units, so we can keep $\phi$ as is. How do we scale length? We could choose to scale the separation by $a$, but in our equations another quantity should be popping out: $p$. Thus, let's define the dimensionless separation $\bar{r} = r/p$. We are not done yet; we also have *time* to worry about. Nicely enough, we have a unit of time that pops out from the $\dot{\phi}$ equation: $t^* \equiv \sqrt{ \frac{p^3}{Gm} }$, which for circular orbits would be the period. We thus define a dimensionless time variable $\bar{t} = t/t^*$. The differential equation thus reduces to
$$
\frac{d\phi}{d \bar{t}} = (1 + e \cos(\phi-\omega))^2
$$
while the separation is simply $\bar{r} = (1+e \cos(\phi-\omega))^{-1}$. To get our physical separation and time back, we just re-scale the output of the IVP solver. Fundamentally, then, you can see that a binary evolves without needing to know the actual mass or semi-latus rectum! These equations can be solved independently of those parameters, and serve only as scales.
