<!-- Evalution Page-->
<?php
	if(!isset($_SESSION['email'])) {
	?>
	<div class = "page-header">
		<div class="card mb-3">
			<div class="card-header">
				<i class="fa fa-area-chart"></i> 평가 (Evalution)
			</div>
			<div class="card-body"><div class="chartjs-size-monitor" style="position: absolute; left: 0px; top: 0px; right: 0px; bottom: 0px; overflow: hidden; pointer-events: none; visibility: hidden; z-index: -1;"><div class="chartjs-size-monitor-expand" style="position:absolute;left:0;top:0;right:0;bottom:0;overflow:hidden;pointer-events:none;visibility:hidden;z-index:-1;"><div style="position:absolute;width:1000000px;height:1000000px;left:0;top:0"></div></div><div class="chartjs-size-monitor-shrink" style="position:absolute;left:0;top:0;right:0;bottom:0;overflow:hidden;pointer-events:none;visibility:hidden;z-index:-1;"><div style="position:absolute;width:200%;height:200%;left:0; top:0"></div></div></div>
				<center>로그인해 주세요<br>(Please Login)</center>
			</div>
		</div>
	</div>

	
	<?php
	} else {
?>
	<center>
	<center>
		<div id="globalWrapper">
			<div id="upMenu">
				<span id="map_name"></span>

			</div>
			<div class="ev_alert">
				<p>마지막 장면에서 선택해주세요</p>
			</div>
			<div class="ev_server_alert">
				<p></p>
			</div>
			<div class="ev_question">
				<button id="closeBt" type="button" class="close" aria-label="Close">
				  <span aria-hidden="true">&times;</span>
				</button>
				<p>Q. 병력이 어디로 이동할 것 같나요?</p>
				<table>
					<tr>
						<td align="center">
						<button class="btn-success answer_button" onclick="pushAnswer('my_camp')" value="my_camp">내 본진</button>
						</td>
						<td align="center">
						<button class="btn-warning answer_button" onclick="pushAnswer('enemy_camp')" value="enemy_camp">적 본진</button>
						</td>
					</tr>
					<tr>
						<td align="center">
						<button class="btn-success answer_button" onclick="pushAnswer('my_multi')" value="my_multi">내 멀티</button>
						</td>
						<td align="center">
						<button class="btn-warning answer_button" onclick="pushAnswer('enemy_multi')" value="enemy_multi">적 멀티</button>
						</td>
					</tr>
					<tr>
						<td align="center">
						<button class="btn-default answer_button"  onclick="pushAnswer('stop')" value="stop">정지</button>
						</td>
						<td align="center">
							<button class="btn-danger answer_button"  onclick="pushAnswer('enemy_force')" value="enemy_force">적 병력</button>
						</td>
					</tr>
				</table>
			</div>
			
			<canvas id="ev_canvas" width="1000" height="1000">
				Your browser does not support the canvas element.
			</canvas>
			<div id="downMenu">
				<!--
				<input type="button" value="Prev" onclick="toPrev()"/>
				<input type="button" value="Next" onclick="toNext()"/>
				-->
				<input type="range" min="0" max="100" value="0" class="slider" id="myRange">
			</div>
		</div>
		
		
	</center>
				
	<script src="https://rawgit.com/nodeca/pako/master/dist/pako.js"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/socket.io/2.0.4/socket.io.js"></script>
	<script>
		var cvs;
		var ctx;
		var bg_ctx;
		var units;
		var rep_json;
		var now_frame;
		
		//IDLE, QUESTION
		var status;
		
		
		var mark_position = null
		
		var env = new Object();
		env.width = 100;
		env.height = 100;
		env.map_name = "";
		env.map_hash = "";
		env.questions= [];
		env.question = [];
		env.next_questions = [];
		env.game_cache = []
		env.file_name = "";
		env.timerStarted = false;
		
		
		$(document).ready(function() {
			connectServer();
			cvs = document.getElementById('ev_canvas')
			ctx = cvs.getContext("2d");
			ctx.fillStyle = "black";
			ctx.fillRect(0, 0, cvs.width, cvs.height);
			resizeCanvas();
			
		});

		$(window).resize(function() {
			resizeCanvas();
		});
		
		$("#ev_canvas").click(function(e) {
			if($("#myRange").val() != env.question.game.length - 1) {
				$(".ev_alert").show();
				var trigger = setInterval(function(){
					$(".ev_alert").hide();
					clearInterval(trigger);
				}, 700);
				return;
			}
			
			
			mouseX = e.pageX - $(this).offset().left;
			mouseY = e.pageY - $(this).offset().top;
			mark_position = [parseInt(mouseX / $(this).width() * env.width), parseInt(mouseY / $(this).height() * env.height)];

			
			$(".ev_question").show();
			renderCanvas();
			
			
		});
		
		
		$(".ev_question #closeBt").click(function(e) {
			$(this).parent().hide();
		});
		
		function resizeCanvas() {
			var sn = $(window);
			var cvs = $('#ev_canvas');
			
			cvs.height(sn.height() - 150);
			cvs.width(cvs.height() * (env.width / env.height));
			
			var evq = $('.ev_question');
			evq.css("top", cvs.height() / 2 - (evq.height() / 2));
			
			var eva = $('.ev_alert, .ev_server_alert');
			eva.css("top", cvs.height() / 4 - (eva.height() / 2));
		}

		function initCanvas() {
			resizeCanvas();
	
			$("#map_name").text("주 병력을 찾아주세요 (Click main force)");
	
			background = new Image();
			$("#myRange").attr("max", env.question.game.length - 1);
			background.src = mapURL;

			background.onload = function() {

				ctx.fillStyle = "black";
				ctx.fillRect(0, 0, cvs.width, cvs.height);

				ctx.globalAlpha = 0.3;
				ctx.drawImage(background , 0, 0, cvs.width, cvs.height);
				ctx.globalAlpha = 1;

				bg_ctx = ctx.getImageData(0, 0, cvs.width, cvs.height);

				renderCanvas();
			}
		}
		var unit_dict =  {
			0: 'Terran_Marine',                                 
			1: 'Terran_Ghost',                                             
			2: 'Terran_Vulture',                                          
			3: 'Terran_Goliath',                                          
			5: 'Terran_Siege_Tank(Tank_Mode)',        
			7: 'Terran_SCV',                                                
			8: 'Terran_Wraith',                                           
			9: 'Terran_Science_Vessel',                          
			11: 'Terran_Dropship',                                    
			12: 'Terran_Battlecruiser',                            
			13: 'Terran_Spider_Mine',             
			14: 'Terran_Nuclear_Missile',                       
			15: 'Terran_Civilian',                                        
			30: 'Terran_Siege_Tank(Tank_Mode)',    
			32: 'Terran_Firebat',                                        
			33: 'Spell_Scanner_Sweep',                          
			34: 'Terran_Medic',                                          
			35: 'Zerg_Larva',                                               
			36: 'Zerg_Egg',                                                   
			37: 'Zerg_Zergling',                                          
			38: 'Zerg_Hydralisk',                                        
			39: 'Zerg_Ultralisk',                                          
			40: 'Zerg_Broodling',                                       
			41: 'Zerg_Drone',                                              
			42: 'Zerg_Overlord',                                         
			43: 'Zerg_Mutalisk',                                          
			44: 'Zerg_Guardian',                                        
			45: 'Zerg_Queen',                                             
			46: 'Zerg_Defiler',                                             
			47: 'Zerg_Scourge',                                          
			50: 'Zerg_Infested_Terran',                          
			58: 'Terran_Valkyrie',                                      
			59: 'Zerg_Cocoon',                                           
			60: 'Protoss_Corsair',                                      
			61: 'Protoss_Dark_Templar',                        
			62: 'Zerg_Devourer',                                       
			63: 'Protoss_Dark_Archon',                           
			64: 'Protoss_Probe',                                         
			65: 'Protoss_Zealot',                                        
			66: 'Protoss_Dragoon',                                   
			67: 'Protoss_High_Templar',                         
			68: 'Protoss_Archon',                                       
			69: 'Protoss_Shuttle',                                       
			70: 'Protoss_Scout',                                          
			71: 'Protoss_Arbiter',                                       
			72: 'Protoss_Carrier',                                       
			73: 'Protoss_Interceptor',                               
			83: 'Protoss_Reaver',                                       
			84: 'Protoss_Observer',                                  
			85: 'Protoss_Scarab',                                       
			89: 'Critter_Rhynadon',                                   
			90: 'Critter_Bengalaas',                                  
			93: 'Critter_Scantid',                                        
			94: 'Critter_Kakaru',                                        
			95: 'Critter_Ragnasaur',                                 
			96: 'Critter_Ursadon',                                      
			97: 'Zerg_Lurker_Egg',                                    
			103: 'Zerg_Lurker',                                           
			105: 'Spell_Disruption_Web',                        
			106: 'Terran_Command_Center',               
			107: 'Terran_Comsat_Station',                    
			108: 'Terran_Nuclear_Silo',                           
			109: 'Terran_Supply_Depot',                        
			110: 'Terran_Refinery',                                   
			111: 'Terran_Barracks',                                  
			112: 'Terran_Academy',                                 
			113: 'Terran_Factory',                                    
			114: 'Terran_Starport',                                   
			115: 'Terran_Control_Tower',                      
			116: 'Terran_Science_Facility',                     
			117: 'Terran_Covert_Ops',                            
			118: 'Terran_Physics_Lab',                            
			120: 'Terran_Machine_Shop',                      
			122: 'Terran_Engineering_Bay',                  
			123: 'Terran_Armory',                                    
			124: 'Terran_Missile_Turret',                       
			125: 'Terran_Bunker',                                     
			130: 'Zerg_Infested_Command_Center',  
			131: 'Zerg_Hatchery',                                      
			132: 'Zerg_Lair',                                                
			133: 'Zerg_Hive',                                               
			134: 'Zerg_Nydus_Canal',                              
			135: 'Zerg_Hydralisk_Den',                           
			136: 'Zerg_Defiler_Mound',                           
			137: 'Zerg_Greater_Spire',                            
			138: 'Zerg_Queens_Nest',                             
			139: 'Zerg_Evolution_Chamber',                 
			140: 'Zerg_Ultralisk_Cavern',                       
			141: 'Zerg_Spire',                                             
			142: 'Zerg_Spawning_Pool',                          
			143: 'Zerg_Creep_Colony',                            
			144: 'Zerg_Spore_Colony',                            
			146: 'Zerg_Sunken_Colony',                         
			149: 'Zerg_Extractor',                                     
			154: 'Protoss_Nexus',                                      
			155: 'Protoss_Robotics_Facility',                  
			156: 'Protoss_Pylon',                                       
			157: 'Protoss_Assimilator',                            
			159: 'Protoss_Observatory',                         
			160: 'Protoss_Gateway',                                 
			162: 'Protoss_Photon_Cannon',                   
			163: 'Protoss_Citadel_of_Adun',                  
			164: 'Protoss_Cybernetics_Core',               
			165: 'Protoss_Templar_Archives',               
			166: 'Protoss_Forge',                                       
			167: 'Protoss_Stargate',                                 
			169: 'Protoss_Fleet_Beacon',                        
			170: 'Protoss_Arbiter_Tribunal',                  
			171: 'Protoss_Robotics_Support_Bay',      
			172: 'Protoss_Shield_Battery',                     
			176: 'Resource_Mineral_Field',                    
			177: 'Resource_Mineral_Field_Type_2',    
			178: 'Resource_Mineral_Field_Type_3',    
			188: 'Resource_Vespene_Geyser',             
			202: 'Spell_Dark_Swarm',                              
			207: 'Special_Pit_Door',                                  
			208: 'Special_Right_Pit_Door',                                                                          
		}
		
		function renderCanvas() {
			// now_frame = idx;
			idx = $("#myRange").val();
			units = env.question.game[idx]
			if(!env.game_cache[idx]) {
				ctx.putImageData(bg_ctx, 0, 0);
				
				ctx.globalAlpha = 0.2;
				for (i in units) {
					u = units[i]
					if(u['ow'] == 0 || (u['ow'] == 1 && u['ve'] == 1)) { 
						arc_x = 1000 *  u['x']/ env.width
						arc_y = 1000 *  u['y']/ env.height

						ctx.beginPath();
						ctx.ellipse(arc_x,arc_y, u['sg'] / 20 * (env.height / env.width), u['sg'] / 20, 0, 2 * Math.PI, false);
						
						if(u['ow'] == 1) {
							ctx.fillStyle = 'red';
						} else {
							ctx.fillStyle = 'blue';
						}
						ctx.fill();
					
					}
					
				}
				ctx.globalAlpha = 1;

				for (i in units) {
					u = units[i]
					if(u['ow'] == 0 || (u['ow'] == 1 && u['ve'] == 1)) { 
						health_rate = (parseInt(u['hp']) + parseInt(u['sp'])) / (parseInt(u['mh']) + parseInt(u['ms']))
						drawUnit(parseInt(u['x']),parseInt(u['y']),parseInt(u['tp']), health_rate, idx, u['ow'], u['sg']);					
					}
				}

				var trigger = setInterval(function(){
					if(unit_stack == 0) {
						env.game_cache[idx] = ctx.getImageData(0, 0, cvs.width, cvs.height);
						clearInterval(trigger);
					}
				}, 1);
			} else {
				ctx.putImageData(env.game_cache[idx], 0, 0);
			}
			
			
			if(mark_position != null && unit_stack == 0) {
				arc_x = 1000 *  mark_position[0]/ env.width
				arc_y = 1000 *  mark_position[1]/ env.height
				  
				  ctx.beginPath();
				  ctx.ellipse(arc_x, arc_y, 30 * (env.height / env.width), 30, 0, 2 * Math.PI, false);
				  ctx.closePath();
				  ctx.fillStyle = 'red';
				  ctx.globalAlpha = 0.6;
				  ctx.fill();
				  ctx.globalAlpha = 1;
			}
			
			if(env.timerStarted == false && idx == env.question.game.length - 1) {
				env.startTime = new Date().getTime();
				env.timerStarted = true;
			}
		}
		var unit_stack = 0
		
		function drawUnit(x, y, type, health_rate, idx, owner, sight) {

			var u = new Image();
			
			unit_stack++;
			
			var unit_str = unit_dict[type];
			u.src = './units/' + unit_str + '.png'
			u.onerror = function(){
				unit_stack--;

			}
			u.onload = function(){
				ctx.globalAlpha = health_rate;

				ctx.drawImage(u , x * (cvs.width / env.width) - this.width * 0.4 * (env.height / env.width) / 2, y * (cvs.height / env.height) - this.height * 0.4 / 2,  this.width * 0.4 * (env.height / env.width), this.height * 0.4);
	
			
				ctx.globalAlpha = 1;
				unit_stack--;
			}
		}

		function pushAnswer(answer) {
			$('.ev_question').hide();
			var endTime = new Date().getTime();
			
			var o = new Object();
			o.frame_count = env.question.frameCount;
			o.force_position = mark_position;
			o.type = env.question.type;
			o.next_action = answer;
			o.elapsed_time = endTime - env.startTime;
			o.mail = "<?php echo $_SESSION['email'];?>";
			o.file_name = env.file_name;
			socket.emit('pushAnswer', JSON.stringify(o));
			
			var result = toNextQuestion();
			if(!result) {
				pullQuestion();
			}
		}

		
		$(document).on('change', '#myRange', function() {
			renderCanvas();
		});
		
		$(document).keydown(function(e) {
			switch(e.which) {
				case 37: // left
					if(unit_stack == 0) {
						if(parseInt($("#myRange").val()) > 0) {
							now = parseInt($("#myRange").val())
							$("#myRange").val(now - 1)
							renderCanvas();
						}
					}
					break;
				case 39: // right
					if(unit_stack == 0) {
						if(parseInt($("#myRange").val()) < env.question.game.length - 1) {
							now = parseInt($("#myRange").val())
							$("#myRange").val(now + 1)
							renderCanvas();
						}
					}
				break;

				default: 
					return;
			}
			e.preventDefault();
		});
		
		var socket = null;
		var mapURL = null;
		
		function connectServer() {
			$(".ev_server_alert p").text("서버에 연결 중 입니다");
			$(".ev_server_alert").show();
			$('.content-wrapper').loading('toggle');
			socket = io.connect("https://cilab.sejong.ac.kr:3000");
			$('.content-wrapper').loading('toggle');
			
			
			
			socket.on('connect', function (socket) {
				$(".ev_server_alert").hide();
				pullQuestion();
			});
			
			
			socket.on('pushMap',function(data){
				mapURL = "https://cilab.sejong.ac.kr/sc/maps/" + data;
				var img = new Image();
				img.src = mapURL;	//Preload
			});
			
			
			socket.on('pushQuestion',function(data){
				var data = pako.inflate(new Uint8Array(data), {to:'string'});
				rep_json = JSON.parse(data);

				env.width = rep_json.map_width;
				env.height = rep_json.map_height;
				env.map_name = rep_json.map_name;
				env.questions = rep_json.list;
				env.file_name = rep_json.file_name;
				
				mark_position = null;
				toNextQuestion();
			});

			socket.on('onError',function(data){
				$(".ev_server_alert p").text(data);
				$(".ev_server_alert").show();
			});
		}
		
		function pullQuestion() {

			socket.emit('pullQuestion', "<?php echo $_SESSION['email'];?>");
			
		}
		
		function toNextQuestion() {
			$('.content-wrapper').loading('toggle');
			if(env.questions.length == 0) {
				$('.content-wrapper').loading('toggle');
				return false;
			}
			
			env.question = env.questions.shift()
			
			env.game_cache = [];
			env.mark_position = null;
			env.timerStarted = [];
			$('#myRange').val(0);
			
			if(env.question.type == '6_status_now') {
				$('#myRange').hide();
			} else if(env.question.type == '6_status_preview') {
				$('#myRange').show();
			}
			
			initCanvas();
			$('.content-wrapper').loading('toggle');
			return true;
		}
	</script>
<?php
	}
?>