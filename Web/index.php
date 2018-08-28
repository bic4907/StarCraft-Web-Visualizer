<?php
	session_start();
	
	$sub_pages = array(
		"main",
		"evalution",
	);
	
	if (!in_array($_GET["pos"], $sub_pages) and !in_array(str_replace("/", "", $_GET["pos"]), $sub_pages)) {
		$_GET["pos"] = "main";
	}
	
	$_SESSION['email'] = "";
?>
<!DOCTYPE html>
<html lang="ko">
	<head>
		<meta charset="utf-8">
		<meta http-equiv="X-UA-Compatible" content="IE=edge">
		<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
		<meta name="description" content="">
		<meta name="author" content="">
		<title>StarCraft Evalution Form</title>
		<link href="https://cilab.sejong.ac.kr/sc/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
		<link href="https://cilab.sejong.ac.kr/sc/vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
		<link href="https://cilab.sejong.ac.kr/sc/css/sb-admin.css" rel="stylesheet">
		<link href="https://cilab.sejong.ac.kr/sc/css/custom.css" rel="stylesheet">
		<link href="https://cilab.sejong.ac.kr/sc/css/jquery.loading.min.css"  rel="stylesheet" tyle="text/css"/>
		<script src="https://cilab.sejong.ac.kr/sc/vendor/jquery/jquery.min.js"></script>
		<script src="https://cilab.sejong.ac.kr/sc/js/jquery.loading.min.js"></script>
	</head>
	<body class="fixed-nav sticky-footer bg-dark" id="page-top">
		<nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top" id="mainNav">
			<a class="navbar-brand" href="./">SC Evalution Form</a>
			<button class="navbar-toggler navbar-toggler-right" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
			</button>
			<div class="collapse navbar-collapse" id="navbarResponsive">
				<ul class="navbar-nav navbar-sidenav" id="exampleAccordion">
					<li class="nav-item" data-toggle="tooltip" data-placement="right" title="메인">
						<a class="nav-link" href="http://cilab.sejong.ac.kr/sc/main">
						<i class="fa fa-fw fa-home"></i>
						<span class="nav-link-text">메인 (Main)</span>
						</a>
					</li>
					<li class="nav-item" data-toggle="tooltip" data-placement="right" title="평가">
						<a class="nav-link" href="http://cilab.sejong.ac.kr/sc/evalution">
						<i class="fa fa-fw fa-dashboard"></i>
						<span class="nav-link-text">평가 (Evalution)</span>
						</a>
					</li>
				</ul>
				<ul class="navbar-nav sidenav-toggler">
					<li class="nav-item">
						<a class="nav-link text-center" id="sidenavToggler">
						<i class="fa fa-fw fa-angle-left"></i>
						</a>
					</li>
				</ul>
				<ul class="navbar-nav ml-auto">
					<li class="nav-item">
						<?php
							if(!isset($_SESSION['email'])) {
								?>
								<a class="nav-link" data-toggle="modal" data-target="#exampleModal">
									<i class="fa fa-fw fa-sign-in"></i>로그인 (Login)</a>
								</a>
								<?php
							} else {
								?>
								<a class="nav-link" href="https://cilab.sejong.ac.kr/sc/logout.php">
									<i class="fa fa-fw fa-sign-in"></i>로그아웃 (Logout)</a>
								</a>
								<?php
							}
						?>
					</li>
				</ul>
			</div>
		</nav>
		<div class="content-wrapper">
			<div class="container-fluid">
				<!-- Content -->
				<?php
					$fileName = str_replace("/","",$_GET["pos"]);
					include_once("sub_".$fileName.".php");
				?>
			</div>
			<footer class="sticky-footer">
				<div class="container">
					<div class="text-center">
						<small>Copyright © CILAB 2018</small>
					</div>
				</div>
			</footer>
			<a class="scroll-to-top rounded" href="#page-top">
			<i class="fa fa-angle-up"></i>
			</a>
			<div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
				<div class="modal-dialog" role="document">
					<div class="modal-content">
						<div class="modal-header">
							<h5 class="modal-title" id="exampleModalLabel">Account</h5>
							<button class="close" type="button" data-dismiss="modal" aria-label="Close">
							<span aria-hidden="true">×</span>
							</button>
						</div>
						<div class="modal-body">
							<center>
								<form action="https://cilab.sejong.ac.kr/sc/login.php" method="POST">
									<div class="form-group">
										<div class="input-group">
											<input id="email" type="email" class="form-control" name="email" placeholder="이메일 (E-mail)">
										</div>
									</div>
									<button type="submit" class="btn btn-success">로그인 (Login)</button>
								</form>
								<hr>
								<p style="margin:0.7em 0;font-size:1.2em;font-weight:600;font-style:italic">OR</p>
								<form action="https://cilab.sejong.ac.kr/sc/join.php" method="POST">
									<div class="form-group">
										<input type="email" class="form-control" id="email" name="email" style="margin:0.2em 0;" placeholder="이메일 (E-mail)">						
										<input type="text" class="form-control" id="name" name="name" style="margin:0.2em 0;" placeholder="이름 (Name)">
										<input type="text" class="form-control" id="belong"  name="belong"style="margin:0.2em 0 1em 0;" placeholder="소속 (Belong)">
										<button type="submit" class="btn btn-primary">회원가입 (Join)</button>
									</div>
								</form>
							</center>
							<hr>
						</div>
					</div>
				</div>
			</div>
		</div>
		<script src="https://cilab.sejong.ac.kr/sc/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
		<script src="https://cilab.sejong.ac.kr/sc/js/sb-admin.min.js"></script>
	</body>
</html>