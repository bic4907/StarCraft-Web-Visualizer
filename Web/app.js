var app = require('express')();
var fs = require('fs');
var mysql = require('mysql');
var format = require('string-format')
var options = {
    key: fs.readFileSync('/var/www/sc/privkey.pem'),
    cert: fs.readFileSync('/var/www/sc/cert.pem'),
};
var https = require('https').Server(options, app);
var io = require('socket.io')(https);
var dateFormat = require('dateformat');
var zlib = require('zlib');
var sizeof = require('object-sizeof');
var iconv = require('iconv-lite');
var stringSimilarity = require('string-similarity');


var mapDic = {
    '투혼':'237_Fighting Spirit',
    'Fighting Spirit':'237_Fighting Spirit',

    '단장의능선': '199_Heartbreak Ridge',
    'Heartbreak Ridge': '199_Heartbreak Ridge',
    '신단장의능선':'267_New Heartbreak Ridge',
    'New Heartbreak Ridge':'267_New Heartbreak Ridge',

    '저격능선': '508_Sniper Ridge',
    'Sniper Ridge': '508_Sniper Ridge',
    '신저격능선': '547_New Sniper Ridge',
    'New Sniper Ridge': '547_New Sniper Ridge',

    '피의능선': '415_Bloody Ridge',
    'Bloody Ridge': '415_Bloody Ridge',
    '신피의능선': '460_New Bloody Ridge',
    'New Bloody Ridge': '460_New Bloody Ridge',

    '태양의제국': '406_Empire of the Sun',
    'Empire of the Sun': '406_Empire of the Sun',
    '신태양의제국': '462_New Empire of the Sun',
    'New Empire of the Sun': '462_New Empire of the Sun',

    '청풍명월': '186_Harmony',
    'Harmony': '186_Harmony',
    '신청풍명월': '194_Neo Harmony',
    'Neo Harmony': '194_Neo Harmony',

    '노스탤지어': '42_Nostalgia',
    'Nostalgia': '42_Nostalgia',

    '데스티네이션': '188_Destination',
    'Destination': '188_Destination',

    'Tau Cross': '3_Tau Cross',
    '타우크로스': '3_Tau Cross',

    'Python': '147_Python',
    '파이썬': '147_Python',

    'Snowbound': '132_Snowbound',
    '스노바운드': '132_Snowbound',

    'Polaris Rhapsody': '275_Polaris Rhapsody',
    '폴라리스랩소디': '275_Polaris Rhapsody',

    'Pathfinder': '409_Pathfinder',
    '패스파인더': '409_Pathfinder',

    '아웃사이더': '200_Outsider',
    'Outsider': '200_Outsider',
    '아웃사이더 SE': '241_Outsider SE',
    'Outsider SE': '241_Outsider SE',

    '네오문글레이브': '265_Neo Moon Glaive',
    'Neo Moon Glaive': '265_Neo Moon Glaive',
    '문글레이브': '239_Moon Glaive',
    'Moon Glaive': '239_Moon Glaive',

    '메두사': '187_Medusa',
    'Medusa': '187_Medusa',
    '네오메두사': '202_Neo Medusa',
    'Neo Medusa': '202_Neo Medusa',

    '레퀴엠': '28_Requiem',
    'Requiem': '28_Requiem',
    '네오레퀴엠': '23_Neo Requiem',
    'Neo Requiem': '23_Neo Requiem',

    '아즈텍': '402_Aztec',
    'Aztec': '402_Aztec',
    '네오아즈텍': '461_Neo Aztec',
    'Neo Aztec': '461_Neo Aztec',

    '매치포인트': '235_Match Point',
    'Match Point': '235_Match Point',

    '라만차': '418_La Manchat',
    'La Mancha': '418_La Mancha',

    '제이드': '507_Jade',
    'Jade': '507_Jade',
    '네오제이드': '545_Neo Jade',
    'Neo Jade': '545_Neo Jade',

    '트로이': '168_Troy',
    'Troy': '168_Troy',

    '블루스톰': '159_Blue Storm',
    'Blue Storm': '159_Blue Storm',

    '안드로메다': '175_Andromeda',
    'Andromeda': '175_Andromeda',

    '그라운드제로': '506_Ground Zero',
    'Ground Zero': '506_Ground Zero',
    '네오그라운드제로': '546_Neo Ground Zero',
    'Neo Ground Zero': '546_Neo Ground Zero',

    '콜로세움': '172_Colosseum',
    'Colosseum': '172_Colosseum',
    '콜로세움2': '192_Colosseum II',
    'Colosseum II': '192_Colosseum II',

    '써킷브레이커': '404_Circuit Breaker',
    'Circuit Breaker': '404_Circuit Breaker',

    '비잔티움': '185_Byzantium',
    'Byzantium': '185_Byzantium',
    '비잔티움2': '191_Byzantium 2',
    'Byzantium2': '191_Byzantium 2',
    '비잔티움3': '197_Byzantium 3',
    'Byzantium3': '197_Byzantium 3',

    '얼터너티브': '459_Alternative',
    'Alternative': '459_Alternative',

    '신용오름': '266_New Tornado',
    'New Tornado': '266_New Tornado',
    '용오름': '232_Tornado',
    'Tornado': '232_Tornado',
    '올드 톨내도': '258_Old Tornado',
    'Old Tornado': '258_Old Tornado',

    '포트리스': '390_Fortress',
    'Fortress': '390_Fortress',
    '포트리스 SE': '435_Fortress SE',
    'Fortress SE': '435_Fortress SE',

    '라이드오브발키리': '16_Ride of Valkyries',
    'Ride of Valkyries': '16_Ride of Valkyries',

    '아웃라이어': '504_Outlier',
    'Outlier': '504_Outlier',
    '네오아웃라이어': '535_Neo Outlier',
    'Neo Outlier': '535_Neo Outlier',

    '오델로': '178_Othello',
    'Othello': '178_Othello',

    '몬티홀': '146_Monty Hall',
    'Monty Hall': '146_Monty Hall',
    '몬티홀 SE': '163_Monty Hall SE',
    'Monty Hall SE': '163_Monty Hall SE',

    '몬테크리스토': '454_Monte Cristo',
    'Monte Cristo': '454_Monte Cristo',

    '루나 더 파이널': '27_Luna the Final',
    'Luna the Final': '27_Luna the Final',

    '로스트 템플': '82_Lost Temple',
    'Lost Temple': '82_Lost Temple',
    '로스트 템플2': '104_Lost Temple 2',
    'Lost Temple 2': '104_Lost Temple 2',
    '네오 로스트 탬플': '47_Neo Lost Temple',
    'Neo Lost Temple': '47_Neo Lost Temple',

    '롱기누스': '7_Longinus',
    'Longinus': '7_Longinus',
    '롱기누스 2': '121_Longinus 2',
    'Longinus 2': '121_Longinus 2',

    '심판의날': '238_Judgment Day',
    'Judgment Day': '238_Judgment Day',

    '이카루스': '403_Icarus',
    'Icarus': '403_Icarus',

    '신의정원': '198_Gods Garden',
    'Gods Garden': '198_Gods Garden',

    '가이아': '24_Gaia',
    'Gaia': '24_Gaia',

    '태풍의눈': '243_Eye of the Storm',
    'Eye of the Storm': '243_Eye of the Storm',

    '일렉트릭써킷': '505_Electric Circuit',
    'Electric Circuit': '505_Electric Circuit',

    '체인리액션': '503_Chain Reaction',
    'Chain Reaction': '503_Chain Reaction',
    '네오체인리액션': '534_Neo Chain Reaction',
    'Neo Chain Reaction': '534_Neo Chain Reaction',

    '벤젠': '407_Benzene',
    'Benzene': '407_Benzene'
}


var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "",
  database : 'sc_evalution'
});


con.connect(function(err) {
    if (err) {
		printLog(FgRed + "DB Connection Error" + FgWhite)
		return;
    }
	printLog("DB Connected");
});

Reset = "\x1b[0m"
Bright = "\x1b[1m"
Dim = "\x1b[2m"
Underscore = "\x1b[4m"
Blink = "\x1b[5m"
Reverse = "\x1b[7m"
Hidden = "\x1b[8m"

FgBlack = "\x1b[30m"
FgRed = "\x1b[31m"
FgGreen = "\x1b[32m"
FgYellow = "\x1b[33m"
FgBlue = "\x1b[34m"
FgMagenta = "\x1b[35m"
FgCyan = "\x1b[36m"
FgWhite = "\x1b[37m"

BgBlack = "\x1b[40m"
BgRed = "\x1b[41m"
BgGreen = "\x1b[42m"
BgYellow = "\x1b[43m"
BgBlue = "\x1b[44m"
BgMagenta = "\x1b[45m"
BgCyan = "\x1b[46m"
BgWhite = "\x1b[47m"


function printLog(param) {
	var d = new Date();
	var d_output = dateFormat(d, "[yyyy/m/d H:MM:ss]");
	if(param == null) { param = ""; }
	console.log(d_output, param);
}

function shuffle(a) {
    for (let i = a.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [a[i], a[j]] = [a[j], a[i]];
    }
    return a;
}

io.on('connection', function(socket){
	printLog(socket.request.connection.remoteAddress + " Connected");

	socket.on('pullQuestion', function(data){
		
		printLog("Pull Question -> " + data);
	
		list = fs.readdirSync(__dirname + '/question/')
		if(!list.length) {
			//Question 파일을 가지고 있지 않을 경우
			printLog(FgCyan + "No Replay " + FgWhite)
			socket.emit('onError', '문제가 미등록 되었습니다');
			return;
		} else {
			//Question 파일을 가지고 있을 경우
			
			var sql = format("SELECT DISTINCT `file` FROM `sc_answer` WHERE `user` = '{}'", data)
			con.query(sql, function (err, result, fields) {
				if (err) {
					printLog(FgRed + "Answer DB Query Error 1" + FgWhite)
					return;
				}

				Object.keys(result).forEach(function(key) {
					var row = result[key];
					list.splice(list.indexOf(row.file), 1);
				});
				
				
				if(list.length == 0) {
					printLog(FgYellow + "Answer Complete -> " + data + FgWhite)
					socket.emit('onError', '더 이상 풀 문항이 없습니다');
					return;
				}

				var list_str = list.map(s => `'${s}'`).join(',');
				var sql = format("SELECT `file` FROM `sc_answer` WHERE `file` IN ({}) AND `file` NOT IN (SELECT DISTINCT `file` FROM `sc_answer` WHERE `user` = '{}') GROUP BY `file` ORDER BY count(`file`) DESC LIMIT 0, 1", list_str, data)
				con.query(sql, function (err, result, fields) {
					if (err) {
						printLog(FgRed + "Answer DB Query Error 2" + FgWhite)
						return;
					}
					var rp_name;
					
					if(result.length == 0) {
						rp_name = list[Math.floor(Math.random() * list.length)];
					} else {
						rp_name = result[0].file;
					}

					var q_path = __dirname + '/question/' + rp_name;


					question_buffer = fs.readFileSync(q_path);
					zlib.inflate(question_buffer, function(err, buf) {
						game_json = iconv.decode(buf, "utf8");
						game = JSON.parse(game_json);
						var matches = stringSimilarity.findBestMatch(game.map_name, Object.keys(mapDic));
						socket.emit('pushMap', mapDic[matches["bestMatch"]["target"]] + ".jpg");
						printLog(FgGreen  + "Map Sended -> " +  mapDic[matches["bestMatch"]["target"]] + ".jpg"  +FgWhite)
						socket.emit('pushQuestion', question_buffer);
						printLog(FgGreen  + "Question Sended -> " + rp_name + " / " + parseInt((sizeof(question_buffer) / 1024)) + "KB" +FgWhite)
					
					});
					
					
					


				});
			});
			
			
			
		}
		
		
		
	});

	
	socket.on('pushAnswer', function(data){
		var obj_answer = JSON.parse(data);
		printLog(obj_answer);
		printLog(FgGreen + "Push Answer <- " + obj_answer.mail + FgWhite);
		var sql = format("INSERT INTO `sc_answer` (`idx`, `user`, `file`, `frame_count`, `force_position`, `next_action`, `elapsed_time`, `type`) VALUES (NULL, '{}', '{}', {}, '{}', '{}', {}, '{}');", obj_answer.mail, obj_answer.file_name, obj_answer.frame_count, obj_answer.force_position, obj_answer.next_action, obj_answer.elapsed_time, obj_answer.type);
		con.query(sql, function(err, result) {
			if (err) {
				
				
				
				
				
				printLog(FgRed + "Answer Update Error " + FgWhite)
				printLog(data);
			} else {
				printLog(FgGreen  + "Answer Updated - "  +  obj_answer.mail +FgWhite)
			}
		});
	});	
});


app.get('/', function(req, res){
  res.send('<h1>StarCraft SocketIO Server</h1>');
});

https.listen(3000, function(){
  printLog("Server Started");
});
    