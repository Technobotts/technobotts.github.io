<script type="text/javascript" src="/date.js"></script>
<script type="text/javascript">
	$(function() {
		var div = $('.timeline');
		$.getJSON('/dates.json', function(data) {
			var groups = $();
			$.each(data.competitions, function() {
				var group = this;
				
				$.each(this.events, function(event) {
					if(this.date instanceof Array) {
						this.endDate = new Date(this.date[1]);
						this.startDate = new Date(this.date[0]);
					} else {
						this.startDate = new Date(this.date);
						this.endDate = this.startDate;
					}
					delete this.date;
					
					if(!group.start || group.start.isAfter(this.startDate))
						group.start = this.startDate;
					if(!group.end || group.end.isBefore(this.endDate))
						group.end = this.endDate;
				});
				
				var groupHolder = $('<a />').attr('href', this.url).addClass('group').data(group).append(
						$('<span />').addClass('arrow').append(
							$('<span />')
						)
					);
				
				$.each(this.events, function(i) {
					var l = (this.startDate - group.start) / (group.end - group.start);
					var w = (this.endDate - this.startDate) / (group.end - group.start);
					$('<div />').addClass('marker').addClass(this.type).css({
						'width': w * 100 + '%',
						'left': l * 100 + '%'
					}).append(
						$('<span />').addClass('label').append(
							$('<span />').append(
								this.type,
								$('<time />').html(
									this.startDate.toString('d{S} MMM').replace('{', '<sup>').replace('}', '</sup>') + 
									(this.endDate != this.startDate ?' - ' + this.endDate.toString('d{S} MMM').replace('{', '<sup>').replace('}', '</sup>') : '')
								)
							)
						)
					).appendTo(groupHolder);
				});
				groups = groups.add(groupHolder);
			});
			var start, end;
			groups.each(function() {
				var d = $(this).data();
				if(!start || start.isAfter(d.start))
					start = d.start;
				if(!end || end.isBefore(d.end))
					end = d.end;
			}).each(function() {
				var d = $(this).data();
				var w = (d.end - d.start)/(end - start);
				var l = (d.start - start)/(end - start);
				$(this).css({
					'width': 100*w + '%',
					'left': 100*l + '%'
				});
			}).appendTo(div).mouseover(function() {
				groups.removeClass('active');
				$(this).addClass('active');
				var competition = $(this).data();
				
				var members = $('<ul />').addClass('members');
				var memberPictures = data.members;
				$.each(competition.teamMembers, function() {
					var member = ""+this;
					$('<li />').appendTo(members).append(
						$('<a />', {
							href: 'https://www.facebook.com/'+memberPictures[member],
							target: '_blank'
						}).append(
							$('<img />').attr('src',
								'https://graph.facebook.com/'
								+ memberPictures[member]
								+ '/picture?type=square'),
							
							$('<span />').text(member)
						)
					);
				});
				
				$('.timeline-info').empty().append(
					$('<header />').text(competition.name),
					$('<div />')
						.addClass('content')
						.append(
							members,
							competition.details
						)
				);
			}).last().mouseover();
			
			(function makeScale() {
				var scale = $('<ol />').addClass('scale');
				var marker = start.clone().add(1).month().set({day: 1});
				while(marker.isBefore(end)) {
					var l = (marker - start)/(end - start);
					var tick = $('<li />').css('left', l*100 + '%');
					if(marker.getMonth() == 0) tick.addClass('year').append(
						$('<div />').append(
							$('<time />').text(marker.getFullYear())
						)
					); 
					tick.appendTo(scale);
					marker = marker.add(1).month();
				}
				scale.prependTo(div);
			})();
		});
	});
</script>
<style type="text/css">
.label {
	position: absolute;
	left:50%;
	white-space: nowrap;
	text-align: center;
}
.label span{
	position: relative;
	left: -50%;
	padding: 5px;
	border-radius: 5px;
}

.timeline {
	padding: 40px 0px 10px;
	position: relative;
	height:20px;
}
.timeline time {
	display: block;
	font-size: 50%;
	color: #404040;
	line-height: 10px;
	font-family: "Arial";
}

.timeline .scale {
	list-style: none;
	margin: 0;
	padding: 0;
	position:relative;
}
.timeline .scale li{
	border-left: 1px solid #a0a0a0;
	height:30px;
	width:0;
	position:absolute;
	top:-5px;
}
.timeline .scale li.year{
	border-left: 1px solid #808080;
}
.timeline .scale li.year div{
	position:absolute;
	bottom:100%;
	margin-left:-0.5px;
}
.timeline .scale li.year time{
	position:relative;
	left:-50%;
	color: #808080;
}
.timeline .group {
	position: absolute;
	border: 1px solid #808080 !important;
	text-shadow: none !important;
	font-weight: normal !important;
	background: #e0e0e0;
	margin: -1px;
	height: 20px;
	display: block;
	
}
.timeline .group .label span {
	display: none;
	background: #e0e0e0;
}

.timeline .group .arrow {
	position: absolute;
	top: 100%;
	left: 50%;
}
.timeline .group.active .arrow span {
	border-left: 10px solid transparent;
	border-right: 10px solid transparent;
	border-bottom: 10px solid #808080;
	margin-left: -10px;
	position: absolute;
	left: -50%;
}

.timeline .group:hover span {
	display: block;
}

.timeline .group .marker {
	background: #FF8000;
	padding: 0px 1px;
	margin: 0px -1px;
	height: 20px;
	position: absolute;
}
.timeline .group .marker .label {
	position: absolute;
	bottom: 100%;
	padding-bottom: 5px;
}
.timeline .group .marker .label span {
	display: none;
	background: #a0a0a0;
	position: relative;
	padding: 5px;
	left:-50%;
	border-radius: 5px;
}

.timeline .group .marker .label span::before {
	content:'';
	border-left: 5px solid transparent;
	border-right: 5px solid transparent;
	border-top: 5px solid #a0a0a0;
	position: absolute;
	bottom: -5px;
	left: 50%;
	margin-left: -5px;
	
}
.timeline .group .marker:hover span {
	display: block;
}
.timeline-info {
	background: #e0e0e0;
	border-radius:5px;
	overflow: hidden;
}
.timeline-info header {
	background: #808080;
	padding: 5px;
}
.timeline-info .content {
	padding: 5px;
	overflow: hidden;
}

.timeline-info .members {
	line-height: 50px;
	float: right;
	list-style: none;
	padding: 0 !important;
	margin: 0 !important;
}
.timeline-info .members li::before {display: none !important; }
.timeline-info .members li{
	float: right;
	width: 50px;
	height: 50px;
	padding: 0;
	margin: 0;
	margin-left: 5px;
	
	-webkit-perspective: 600;
	position: relative
}
.timeline-info .members li * {
	position: absolute;
	top: 0;
	left: 0;
	width: inherit;
	height: inherit;
	-webkit-transform-style: preserve-3d;
	-webkit-backface-visibility: hidden;
	-webkit-transition: all .4s ease-in-out;
}
.timeline-info .members li a {border: none !important;}
.timeline-info .members li img {
	z-index: 900;
	-webkit-transform: rotateY(0deg);
	background: white url(/images/ajaxSpinner.gif) no-repeat 50% 50%;
}

.timeline-info .members li span {
	z-index: 800;
	-webkit-transform: rotateY(-180deg);
	text-align: center;
	background: #c0c0c0;
	font-size: 0.8em;
}

.timeline-info .members li:hover img {
	z-index: 900;
	-webkit-transform: rotateY(180deg);
}

.timeline-info .members li:hover span {
	z-index: 1000;
	-webkit-transform: rotateY(0deg);
}
</style>
<div class="timeline"></div>
<div class="timeline-info">
	<!--<header>Hover to show details</header>
	<div class="content">
		Constructed from the json file <a href="/dates.json">here</a>.
	</div>-->
</div>
