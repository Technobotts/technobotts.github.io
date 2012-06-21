<p>
	This year, the team have decided to enter a different competition to
	before, called RoboCup Soccer. Two "teams" of autonomous robots, each
	consisting of 1 or 2 robots, have to play against each other in a robotic
	football match.
</p>
<section>
	<h2>The competition</h2>
	<p>
		The robots play on a 72&Prime; by 48&Prime; field, with 5&frac12;&Prime;
		high wall around the edge. The wall is painted black, and the field consists
		of green carpet tiles. There is a 17&frac34;&Prime; goal at either end, painted
		yellow or blue.
	</p>
	<p>
		The robots play with a specially designed ball, with 20 IR-emitting LEDS. This
		enables the robots to see the ball.
	</p>
	<p>
		Each robot must be completely autonomous, and must fit within a 22cm cylinder
		when fully extended. It must also have a handle on the top, to allow the referee
		to pick it up.
	</p>
</section>
<section>
	<h2>UK finals</h2>
	<div class="object-box">
		<iframe width="640" height="360" src="http://www.youtube.com/embed/deIhmEFZ1co?rel=0&wmode=transparent" frameborder="0" allowfullscreen></iframe>
		<span class="caption">The Robocup Soccer UK Final 2011</span>
		<iframe width="640" height="360" src="http://www.youtube.com/embed/hqdBJPGkoOg?rel=0&wmode=transparent" frameborder="0" allowfullscreen></iframe>
		<span class="caption">The Robocup Soccer UK Final 2010</span>
		<img src="/images/Robot.png" alt="Robot and trophy"/>
		<span class="caption">Our robot and trophy</span>
	</div>
	<p>
		In March, we went to the UK Finals in Birkenhead. There, we participated in the
		Soccer and Rescue competitions. We won all our Soccer games, with score exceeding
		7:0, except for one game, where a stupid mistake was inserted into the code to fix
		a minor bug. Nevertheless, we came out with a trophy, and a big congratulations. You
		can see a video of the final above. As a result, we qualified for
		<a href="http://robocup2010.org/">Robocup 2010</a>, in Singapore.
	</p>
</section>
<section>
	<h2>Singapore</h2>
	<p>
		Since the UK final in March, which was played 1-on-1, the team has
		completed its second robot and almost completely redesigned the first
		one, to take into account the different requirements for the
		international competition. We've made contact with Iranian and Portuguese
		teams already &mdash; both vastly more experienced than us &mdash; and are awaiting
		our matches with some trepidation. We spent a while attempting to design
		a solenoid ball kicker but in the end there was not sufficient time to
		complete this, so we are sticking with the original design, powered by a
		Lego motor.
	</p>
</section>
<section>
	<h2>The robots</h2>
	<p>
		Given our previous experience in lego robotics competitions, we decided to
		use the LEGO Mindstorms NXT robotics kit. However, we soon found out that we
		did not have enough kits, particularly since one of our kits was used in an
		old robot to demo at the Big Bang Science Fair. Thankfully, John Lewis donated
		two shiny new NXT 2.0 kits to the team, which we are incredibly grateful for.
		In thanks, we've named our robots &ldquo;John&rdquo; and &ldquo;Lewis&rdquo;!
	</p>
	<div class="object-box">
		<img src="/images/John and Lewis.jpg"/>
		<span class="caption">Our two soccer robots, John and Lewis</span>
	</div>
	<a name="3D-spin"></a>
	<div class="object-box left" id="robot-spin">
		<a href="javascript: setup3DSpin()">
			<img src="/images/3d-spin/robot (0).jpg" title="Click to load the 3D spin (4MB)!"/>
		</a>
		<span class="caption">A 3D spin of our robot, John</span>
	</div>
	<p>
		The 2 robots are shown above. The one on the left is John, the forward
		robot, which now has image recognition built in using the on-board
		camera, so that it can differentiate between the blue (or yellow) goal
		and the black end wall of the pitch, to improve accuracy in shooting at the
		goal, after it has used the compass sensor to orient itself and get the
		ball to the right end of the pitch. It also uses 2 IR-seeker sensors to
		let it detect the ball with improved accuracy, and has an ultrasonic sensor
		so it can determine when it has the ball in its possession.
	</p>
	<p>
		The one on the right is Lewis, the goalie robot, which uses a compass sensor,
		one IR-seeker, one ultrasonic sensor, and a touch sensor. Its task is to stay
		near the goal it is defending and to try to keep the ball out of it.
	</p>
	<p>
		Both robots are programmed using LeJOS NXJ, a Java language for the NXT
		brick.
	</p>
</section>
