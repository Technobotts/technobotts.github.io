var navAnimTime = 100;
var footerAnimTime = 500;

$.event.special.fixedload = {
	add: function (hollaback) {
		var blank = "data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///ywAAAAAAQABAAACAUwAOw==";
		
		$(this).filter(function() {
			if (this.complete) {
				hollaback.handler.call(this);
				return false;
			}
			return true;
		}).bind('load',function(){
			if (this.src !== blank) { hollaback.handler.call(this); }
		}).each(function(){
			// cached images don't fire load sometimes, so we reset src.
			if (this.complete === undefined) {
				var src = this.src;
				// webkit hack from http://groups.google.com/group/jquery-dev/browse_thread/thread/eee6ab7b2da50e1f
				// data uri bypasses webkit log warning (thx doug jones)
				this.src = blank;
				this.src = src;
			}  
		}); 
	
	}
};

$.fn.imageGallery = function(options) {
	options = $.extend({
		fadeTime: 0,
		smoothScroll: 0
	}, options);
	
	$(this).each(function() {
		var container = $(this);
		var imagesArray = container.children().not('.caption').map(function() {
			return {
				media: $(this),
				caption: $(this).nextAll('.caption').eq(0).clone()
			};
		}).get();
		
		var index = container.attr('data-random') == 'true' ?
			Math.floor(Math.random()*imagesArray.length) : 0;
		var lastIndex = index;
		
		var mediaWrapper = $('<div/>', {
			'class':'media'
		}).append(imagesArray[index].media);
		/*$.each(imagesArray, function() {
			this.media.addClass('loading').bind('fixedload', function() {
				$(this).removeClass('loading');
				console.log("U MAD");
			});
		});*/
		container
			.addClass('multiple')
			.empty()
			.append(mediaWrapper)
			.append(
				$('<div/>', {
					'class':'controls'
				}).append(
					$('<button/>',{
						'class': 'previous-button',
						'title': 'previous',
					}).text('\u25C0').mousedown(prevStart)
				).append(
					$('<button/>',{
						'class': 'next-button',
						'title': 'next'
					}).text('\u25B6').mousedown(nextStart)
				)
			)
			.append(imagesArray[index].caption);
			
		var prevIntervalId = false;
		function prev()
		{
			index--;
			update();
		}
		function prevStart()
		{
			prev();
			
			if(prevIntervalId === false && options.smoothScroll != 0) {
				prevIntervalId = setInterval(prev,options.smoothScroll);
				$(document).one('mouseup', prevEnd);
			}
		}
		function prevEnd()
		{
			if(prevIntervalId !== false) {
				clearInterval(prevIntervalId);
				prevIntervalId = false;
			}
		}
		var nextIntervalId = false;
		function next()
		{
			index++;
			update();
		}
		function nextStart()
		{
			next();

			if(nextIntervalId === false && options.smoothScroll != 0)
			{
				nextIntervalId = setInterval(next,options.smoothScroll);
			}
			$(document).one('mouseup', nextEnd);
		}
		function nextEnd()
		{
			if(nextIntervalId !== false)
			{
				clearInterval(nextIntervalId);
				nextIntervalId = false;
			}
		}
		
		function update()
		{			
			//Calculate new index
			var size = imagesArray.length;
			index = (index + size)%size;
			
			var current = imagesArray[index];
			var previous = imagesArray[lastIndex];
			
			var oldHeight = mediaWrapper.height();
			var oldWidth = mediaWrapper.width();
			
			previous.media.remove();
			mediaWrapper.append(current.media);
			previous.caption.remove();
			
			var newHeight = mediaWrapper.height();
			var newWidth = mediaWrapper.width();
			
			
			container.append(current.caption.css('max-width', newWidth - 60));
			
			
			var sizeDiff = (Math.abs(oldHeight - newHeight) +
			                Math.abs(oldWidth  - newWidth )) / 2;
		
			if(options.smoothScroll == 0) current.media.hide();
			
			mediaWrapper
				.css({
					height: oldHeight,
					width: oldWidth
				})
				.animate({
						height: newHeight,
						width: newWidth
					}, options.smoothScroll == 0 ? 5 * sizeDiff : options.smoothScroll/2, function() {
						$(this).css({
							height: 'auto',
							width: 'auto'
						})
						if(options.smoothScroll == 0)
							current.media.show();
					}
				);
				
				
			lastIndex = index;
		}
	})
}

function setup3DSpin()
{
	var imgCount = 36;
	var container = $('#robot-spin');
	var loaded = 0;
	var images = [];
	var status = container.find('a');
	status.find('img').remove();
	function onLoad()
	{
		loaded++;
		status.text(Math.floor(loaded / imgCount * 100) + '%');
		if(loaded >= imgCount)
		{
			status.text('Done!');
			setTimeout(function() {
				$.each(images,function() {
					container.prepend(this);
				});
				status.remove();
				container.imageGallery({smoothScroll: 100});
			}, 500);
		}
	}
	for(var i = imgCount-1; i >= 0; i--)
	{
		images.push(
			$('<img>')
				.attr('alt', 'View from '+(i*360/imgCount)+'\u00B0')
				.attr('src', '/images/3d-spin/robot ('+i+').jpg')
				.each(function() {
					if(this.complete) onLoad();
					else $(this).one('load',onLoad)
				})
		);
	}
}

$(document).ready(function() {
	$('.object-box').filter(function() {
		return $(this).children().not('.caption').length > 1;
	}).imageGallery();
	//$('#navbar li').prepend($('<span/>',{'class':'round-left'})).append($('<span/>',{'class':'round-right'}));
	$('#navbar li:not(.current) a').hover(function() {
		$(this)
			.stop(1,0)
			.animate({
				'padding-top': '5px'
			}, navAnimTime);
	}, function() {
		$(this)
			.stop(1,0)
			.animate({
				'padding-top': '2.5px'
			}, navAnimTime);
	});
			
	
	$('#footer-main').mouseenter(function() {
		$(this)
			.stop(1,0)
			.animate({
				marginTop: '0px'
			}, footerAnimTime);
	});
	$('#footer').mouseleave(function() {
		var footer = $(this).find('#footer-main');
		var margin = $(this).innerHeight()-footer.outerHeight()+'px';
		footer.stop(1,0)
			.animate({
				marginTop: margin
			}, footerAnimTime);
	});
});