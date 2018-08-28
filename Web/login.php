<?php
	session_start();

	$db = mysqli_connect("localhost", "root", "sourcefish", "sc_evalution");
	if (mysqli_connect_errno()) {
		printf("Connect failed: %s\n", mysqli_connect_error());
		die();
	}
	$sql = "SELECT * FROM `sc_users` WHERE `mail` = '".mysqli_real_escape_string($db, $_POST['email'])."'";
	$result = mysqli_query($db, $sql);

	if(mysqli_num_rows($result) == 1) {
		$_SESSION['email'] = mysqli_real_escape_string($db, $_POST['email']);
	} else {
		?>
			<script>alert('존재하지 않는 이메일 입니다\nNo exist E-mail');</script>
		<?php
		
	}
?>
<script>location.href="https://cilab.sejong.ac.kr/sc/";</script>