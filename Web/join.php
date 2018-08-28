<?php
	session_start();

	$db = mysqli_connect("localhost", "root", "sourcefish", "sc_evalution");
	if (mysqli_connect_errno()) {
		printf("Connect failed: %s\n", mysqli_connect_error());
		die();
	}

	$email = mysqli_real_escape_string($db, $_POST['email']);
	$name = mysqli_real_escape_string($db, $_POST['name']);
	$belong = mysqli_real_escape_string($db, $_POST['belong']);
	
	
	$sql = "INSERT INTO `sc_users` (`mail`, `name`, `belong`) VALUES ('$email', '$name', '$belong')";

	$result = mysqli_query($db, $sql);

	if ($result) {
		//회원가입 성공
		$_SESSION['email'] = $email;
		?>
			<script>alert('회원가입 성공!\nJoin Success!');</script>
		<?php
	} else {
		//회원가입 실패
		?>
			<script>alert('에러\nError');</script>
		<?php
	}
?>
<script>location.href="https://cilab.sejong.ac.kr/sc/";</script>
