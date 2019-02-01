/**
  * isMobile
  * responsiveMenu
  * headerFixed
  * ajaxContactForm
  * alertBox
  * testimonialSlide
  * flatTestimonials
  * flatTestimonialsStyle1
  * progressBar
  * flatTeam
  * flatTeamNomargin
  * twitterFeed
  * portfolioIsotope
  * portfolioCarosuel
  * progressCircle
  * detectViewport
  * counter
  * tabs
  * woocommerceTabs  
  * flatClient
  * flatClientSt1
  * featuredPost
  * flatServices
  * blogMasory
  * googleMap
  * togglesAccordion
  * responsiveVideo 
  * goTop
  * retinaLogos
  * parallax
  * removePreloader
*/

;(function($) {

   'use strict'

    var isMobile = {
        Android: function() {
            return navigator.userAgent.match(/Android/i);
        },
        BlackBerry: function() {
            return navigator.userAgent.match(/BlackBerry/i);
        },
        iOS: function() {
            return navigator.userAgent.match(/iPhone|iPad|iPod/i);
        },
        Opera: function() {
            return navigator.userAgent.match(/Opera Mini/i);
        },
        Windows: function() {
            return navigator.userAgent.match(/IEMobile/i);
        },
        any: function() {
            return (isMobile.Android() || isMobile.BlackBerry() || isMobile.iOS() || isMobile.Opera() || isMobile.Windows());
        }
    };

	var responsiveMenu = function() {
        var menuType = 'desktop';

        $(window).on('load resize', function() {
            var currMenuType = 'desktop';

            if ( matchMedia( 'only screen and (max-width: 991px)' ).matches ) {
                currMenuType = 'mobile';
            }

            if ( currMenuType !== menuType ) {
                menuType = currMenuType;

                if ( currMenuType === 'mobile' ) {
                    var $mobileMenu = $('#mainnav').attr('id', 'mainnav-mobi').hide();
                    var hasChildMenu = $('#mainnav-mobi').find('li:has(ul)');

                    $('#header').after($mobileMenu);
                    hasChildMenu.children('ul').hide();
                    hasChildMenu.children('a').after('<span class="btn-submenu"></span>');
                    $('.btn-menu').removeClass('active');
                } else {
                    var $desktopMenu = $('#mainnav-mobi').attr('id', 'mainnav').removeAttr('style');

                    $desktopMenu.find('.submenu').removeAttr('style');
                    $('#header').find('.nav-wrap').append($desktopMenu);
                    $('.btn-submenu').remove();
                }
            }
        });

        $('.btn-menu').on('click', function() {         
            $('#mainnav-mobi').slideToggle(300);
            $(this).toggleClass('active');
        });

        $(document).on('click', '#mainnav-mobi li .btn-submenu', function(e) {
            $(this).toggleClass('active').next('ul').slideToggle(300);
            e.stopImmediatePropagation()
        });
    }

    var headerFixed = function() {        

        if ( $('body').hasClass('header-sticky') ) {
            var hd_height = $('#header').height();           
            $(window).on('load scroll', function(){                
                if ( $(window).scrollTop() > hd_height + 30 ) {
                    $('#header').addClass('downscrolled');                      
                } else {                    
                    $('#header').removeClass('downscrolled');                   
                }
                if( $(window).scrollTop() > 300 ) {
                    $('#header').addClass('upscrolled');                    
                } else {
                    $('#header').removeClass('upscrolled');                    
                }
            })            
        }   
    }


    var alertBox = function() {
        $(document).on('click', '.close', function(e) {
            $(this).closest('.flat-alert').remove();
            e.preventDefault();
        })     
    }  
   
    var testimonialSlide = function() {
        $('.flat-testimonials-slider').each(function(){
            $(this).children('#flat-testimonials-carousel').flexslider({
                animation: "slide",
                controlNav: false,
                animationLoop: true,
                slideshow: true,
                itemWidth: 70,
                itemMargin: 30,
                asNavFor: $(this).children('#flat-testimonials-flexslider')
            });
            $(this).children('#flat-testimonials-flexslider').flexslider({
                animation: "slide",
                controlNav: false,
                animationLoop: true,
                slideshow: true,                
                sync: $(this).children('#flat-testimonials-carousel'),
                prevText: '<i class="fa fa-angle-left"></i>',
                nextText: '<i class="fa fa-angle-right"></i>'
            });
        });
    };   

    var flatTestimonialsStyle1 = function() {
        $('.flat-row').each(function() {            
            if ( $().owlCarousel ) {
                $(this).find('.flat-testimonials-style1').owlCarousel({
                    loop: true,
                    margin: 30,
                    nav: $('.flat-testimonials-style1').data('nav'),
                    dots: $('.flat-testimonials-style1').data('dots'),                     
                    autoplay: $('.flat-testimonials-style1').data('auto'),                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        767:{
                            items: 1
                        },
                        991:{
                            items: 1
                        },
                        1200: {
                            items: $('.flat-testimonials-style1').data('item')
                        }
                    }
                });
            }
        });
    };    

    var progressBar = function() {
        $('.progress-bar').on('on-appear', function() {
            $(this).each(function() {
                var percent = $(this).data('percent');

                $(this).find('.progress-animate').animate({
                    "width": percent + '%'
                },3000);

                $(this).parent('.flat-progress').find('.perc').addClass('show').animate({
                    "width": percent + '%'
                },3000);
            });
        });
    };

    var flatTeam = function() {
        $('.flat-row').each(function() {               
            if ( $().owlCarousel ) {
                $(this).find('.flat-team-carosuel').owlCarousel({
                    loop: true,
                    margin: 0,
                    nav: $('.flat-team-carosuel').data('nav'),
                    dots: $('.flat-team-carosuel').data('dots'),                     
                    autoplay: $('.flat-team-carosuel').data('auto'),                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        767:{
                            items: 1
                        },
                        991:{
                            items: 1
                        },
                        1200: {
                            items: $('.flat-team-carosuel').data('item')
                        }
                    }
                });
            }
        });
    };

    var flatTeamNomargin = function() {
        $('.flat-row').each(function() {                
            if ( $().owlCarousel ) {
                $(this).find('.flat-team-carosuel-nomargin').owlCarousel({
                    loop: true,
                    margin: 0,
                    nav: true,
                    dots: false,                     
                    autoplay: false,                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        767:{
                            items: 1
                        },
                        991:{
                            items: 1
                        },
                        1200: {
                            items: 5
                        }
                    }
                });
            }
        });
    };

    var twitterFeed = function () {
        if ( $().tweet ) {
            $('.list-tiwtter').each(function () {
                var $this = $(this);
                $this.tweet({
                    username: $this.data('username'),
                    join_text: "auto",
                    avatar_size: null,
                    count: $this.data('number'),
                    template: "{text}",
                    loading_text: "loading tweets...",
                    modpath: $this.data('modpath')      
                }); // tweet
            }); // lastest-tweets each
        };
    }; 

    var portfolioIsotope = function() {         
        if ( $().isotope ) {           
            var $container = $('.portfolio-wrap');
            $container.imagesLoaded(function(){
                $container.isotope({
                    itemSelector: '.item',
                    transitionDuration: '1s'
                });
            });

            $('.portfolio-filter li').on('click',function() {                           
                var selector = $(this).find("a").attr('data-filter');
                $('.portfolio-filter li').removeClass('active');
                $(this).addClass('active');
                $container.isotope({ filter: selector });
                return false;
            });            
        };
    };

    var portfolioCarosuel = function() {
        $('.related-portfolio').each(function() {            
            if ( $().owlCarousel ) {
                $(this).find('.portfolio-carosuel').owlCarousel({
                    loop: true,
                    margin: 30,
                    nav: $('.portfolio-carosuel').data('nav'),
                    dots: $('.portfolio-carosuel').data('dots'),                     
                    autoplay: $('.portfolio-carosuel').data('auto'),                    
                    responsive:{
                        0:{
                            items: 2
                        },
                        767:{
                            items: 2
                        },
                        991:{
                            items: 2
                        },
                        1200: {
                            items: $('.portfolio-carosuel').data('item')
                        }
                    }
                });
            }
        });
    };    

    var progressCircle = function() {
        $('.flat-progress-circle').on('on-appear', function() {
            $(this).each(function() {
                if ( $().easyPieChart ) {
                    $(this).easyPieChart({
                        lineWidth: 5,
                        barColor: '#feb800',
                        trackColor: '#ebebeb',
                        scaleColor: false,
                        animate: 3000,
                        lineCap: 'square',
                        onStep: function(from, to, value) {
                            $(this.el).find('.inner-circle span:eq(1)').text(~~value);
                        }
                    });
                }
            });
        });
    };

    var detectViewport = function() {
        $('[data-waypoint-active="yes"]').waypoint(function() {
            $(this).trigger('on-appear');
        }, { offset: '90%', triggerOnce: true });

        $(window).on('load', function() {
            setTimeout(function() {
                $.waypoints('refresh');
            }, 100);
        });
    };

    var counter = function() {
        $('.flat-counter').on('on-appear', function() { 
            $(this).find('.numb-count').each(function() { 
                var to = parseInt( ($(this).attr('data-to')),10 ), speed = parseInt( ($(this).attr('data-speed')),10 );
                if ( $().countTo ) {
                    $(this).countTo({
                        to: to,
                        speed: speed
                    });
                }
            });
       });
    };
       
    var tabs = function() {
        $('.flat-tabs').each(function() {

            $(this).children('.content-tab').children().hide();
            $(this).children('.content-tab').children().first().show();

            $(this).find('.menu-tab').children('li').on('click', function(e) {
                var liActive = $(this).index(),
                    contentActive = $(this).siblings().removeClass('active').parents('.flat-tabs').children('.content-tab').children().eq(liActive);

                contentActive.addClass('active').fadeIn('slow');
                contentActive.siblings().removeClass('active');
                $(this).addClass('active').parents('.flat-tabs').children('.content-tab').children().eq(liActive).siblings().hide();
                e.preventDefault();
            });
        });
    };

    var woocommerceTabs = function() {
        $('.woocommerce-tabs').each(function() {
           var content = $('.entry-content .content-inner');
            content.hide();
            if ( (content).hasClass("active")) {
                $('.entry-content .content-inner.active').show();
            } else {
                content.first().show();
            }                     
            $(this).find(' > ul > li').on('click',function(e) {                
                var hid = $(this).index();
                e.preventDefault();
                $(this).siblings().removeClass('active');
                $(this).addClass('active');
                var contentActive = $(this).parents('.tabs').siblings('.entry-content').children('.content-inner').eq(hid);                
                content.not(':eq(hid)').hide();
                contentActive.fadeIn(300);                
            })
        });
    };
  
    var flatTestimonials = function() {
        $('.flat-row').each(function() {            
            if ( $().owlCarousel ) {
                $(this).find('.flat-testimonials').owlCarousel({
                    loop: true,
                    margin: 30,
                    nav: $('.flat-testimonials').data('nav'),
                    dots: $('.flat-testimonials').data('dots'),                     
                    autoplay: $('.flat-testimonials').data('auto'),                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        767:{
                            items: 1
                        },
                        991:{
                            items: 1
                        },
                        1200: {
                            items: $('.flat-testimonials').data('item')
                        }
                    }
                });
            }
        });
    };

    var flatClient = function() {
        $('.flat-row').each(function() {            
            if ( $().owlCarousel ) {
                $(this).find('.flat-client').owlCarousel({
                    loop: true,
                    margin: $('.flat-client').data('margin'),
                    nav: $('.flat-client').data('nav'),
                    dots: $('.flat-client').data('dots'),                     
                    autoplay: $('.flat-client').data('auto'),                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        480:{
                            items: 2
                        },
                        767:{
                            items: 3
                        },
                        991:{
                            items: 3
                        },
                        1200: {
                            items: $('.flat-client').data('item')
                        }
                    }
                });
            }
        });
    };

    var flatClientSt1 = function() {
        $('.flat-row').each(function() {            
            if ( $().owlCarousel ) {
                $(this).find('.flat-client.style1').owlCarousel({
                    loop: true,
                    margin: 15,
                    nav: $('.flat-client.style1').data('nav'),
                    dots: $('.flat-client.style1').data('dots'),                     
                    autoplay: $('.flat-client.style1').data('auto'),                    
                    responsive:{
                         0:{
                            items: 2
                        },
                        480:{
                            items: 2
                        },
                        767:{
                            items: 3
                        },
                        991:{
                            items: 3
                        },
                        1200: {
                            items: $('.flat-client.style1').data('item')
                        }
                    }
                });
            }
        });
    };     

    var featuredPost = function() {
        $('.widget.widget-featured-post').each(function() {                
            if ( $().owlCarousel ) {
                $(this).find('.widg-featured-post').owlCarousel({
                    loop: true,
                    margin: 0,
                    nav: $('.flat-team-carosuel').data('nav'),
                    dots: $('.flat-team-carosuel').data('dots'),                     
                    autoplay: $('.flat-team-carosuel').data('auto'),                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        767:{
                            items: 1
                        },
                        991:{
                            items: 1
                        },
                        1200: {
                            items: 1
                        }
                    }
                });
            }
        });
    }; 

    var flatServices = function() {
        $('.flat-row').each(function() {               
            if ( $().owlCarousel ) {
                $(this).find('.flat-services-carousel').owlCarousel({
                    loop: true,
                    margin: 0,
                    nav: $('.flat-services-carousel').data('nav'),
                    dots: $('.flat-services-carousel').data('dots'),                     
                    autoplay: $('.flat-services-carousel').data('auto'),                    
                    responsive:{
                        0:{
                            items: 1
                        },
                        767:{
                            items: 1
                        },
                        991:{
                            items: 1
                        },
                        1200: {
                            items: $('.flat-services-carousel').data('item')
                        }
                    }
                });
            }
        });
    };

    var blogMasory = function() {         
        if ( $().isotope ) {           
            var $container = $('.post-wrap');
            $container.imagesLoaded(function(){
                $container.isotope({
                    itemSelector: '.entry',
                    transitionDuration: '1s'
                });
            });           
            
        };
    };

    var sectionVideo = function () {
        if($().YTPlayer) {
            $(".video-section").YTPlayer( {
                showControls: false,
                autoPlay: false
            }); 
            var v = $('.video-section');
            $('#video-controls a')
            .each(function() {
                var t = $(this);
                t.on('click', (function(e) {
                    e.preventDefault();  
                    if (t.hasClass('fa-play')) {
                        t.removeClass('fa-play')
                            .addClass(
                                'fa-pause');
                        v.playYTP();
                        return false
                    }                  
                    if (t.hasClass('fa-pause')) {
                        t.removeClass(
                                'fa-pause')
                            .addClass('fa-play');
                        v.pauseYTP();
                        return false
                    }                    
                }));
            });
        }
    }   



    var togglesAccordion = function() {
        var args = {duration: 600};
        $('.flat-toggle .toggle-title.active').siblings('.toggle-content').show();

        $('.flat-toggle.enable .toggle-title').on('click', function() {
            $(this).closest('.flat-toggle').find('.toggle-content').slideToggle(args);
            $(this).toggleClass('active');
        }); // toggle 

        $('.flat-accordion .toggle-title').on('click', function () {
            if( !$(this).is('.active') ) {
                $(this).closest('.flat-accordion').find('.toggle-title.active').toggleClass('active').next().slideToggle(args);
                $(this).toggleClass('active');
                $(this).next().slideToggle(args);
            } else {
                $(this).toggleClass('active');
                $(this).next().slideToggle(args);
            }     
        }); // accordion
    };


    var responsiveVideo= function() {
        if ( $().fitVids ) {
            $('.container').fitVids();
        }
    };

    var flatAnimation = function() {
        if ( isMobile.any() == null ) {
            $('.flat-animation').each( function() {
                var flatElement = $(this),
                    flatAnimationClass = flatElement.data('animation'),
                    flatAnimationDelay = flatElement.data('animation-delay'),
                    flatAnimationOffset = flatElement.data('animation-offset');

                flatElement.css({
                    '-webkit-animation-delay':  flatAnimationDelay,
                    '-moz-animation-delay':     flatAnimationDelay,
                    'animation-delay':          flatAnimationDelay
                });

                flatElement.waypoint(function() {
                    flatElement.addClass('animated').addClass(flatAnimationClass);
                },{
                    triggerOnce: true,
                    offset: flatAnimationOffset
                });
            });
        }
    };
   
    var goTop = function() {
        $(window).scroll(function() {
            if ( $(this).scrollTop() > 800 ) {
                $('.go-top').addClass('show');
            } else {
                $('.go-top').removeClass('show');
            }
        }); 

        $('.go-top').on('click', function() {            
            $("html, body").animate({ scrollTop: 0 }, 1000 , 'easeInOutExpo');
            return false;
        });
    };

    var retinaLogos = function() {
      var retina = window.devicePixelRatio > 1 ? true : false;


    };    
    
    var parallax = function() {
        if ( $().parallax && isMobile.any() == null ) {
            $('.parallax1').parallax("50%", 0.2);
            $('.parallax2').parallax("50%", 0.4);  
            $('.parallax3').parallax("50%", 0.5);            
        }
    };

    var removePreloader = function() {        
        $('.loading-overlay').fadeOut('slow',function () {
            $(this).remove();
        });
    };

   	// Dom Ready
	$(function() {
        $(".nav-wrap").click(function () {
            console.log("sdsdsdsdssssssss")
            window.scrollTo(0, 0)
        })
        if ( matchMedia( 'only screen and (min-width: 991px)' ).matches ) {
            headerFixed();
        }   
        responsiveMenu();
        portfolioIsotope(); 
        portfolioCarosuel();
        flatTeam();
        flatTeamNomargin();
        counter(); 
        progressCircle();       
        testimonialSlide();
        flatTestimonials();
        flatTestimonialsStyle1();
        progressBar();
        flatClient();
        flatClientSt1();
        togglesAccordion();    
        tabs(); 
        featuredPost();
        flatServices();
        blogMasory(); 
        alertBox();
        twitterFeed();
        woocommerceTabs();
        detectViewport(); 
        sectionVideo();
        flatAnimation();
        goTop();
        responsiveVideo();
        retinaLogos(); 
        parallax();
        removePreloader();

   	});

})(jQuery);