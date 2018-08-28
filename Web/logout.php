<?php
	session_start();
	session_destroy();
	
	header("Location: https://cilab.sejong.ac.kr/sc/main");
?>