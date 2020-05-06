<?php
include "conecta.php";

    $status = $_GET['status'];
    $data = date ('Y/m/d H:i:s');
	
	
	if($status == 0){
		$sql = "INSERT INTO sensor_energia (status) VALUES ($status)";
		if (mysqli_query($conn, $sql)) {
		
          echo "Valores salvo com sucesso!";
		} else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}
	
	if($status == 1){
		
		$consulta = "select * from sensor_energia where status = 0 and data2 is NULL";
		$resultado = mysqli_query($conn,$consulta) or die("Erro ao retornar dados");
	
		while ($registro = mysqli_fetch_array($resultado)){
			$id = $registro['id'];
		}
		$update = "update sensor_energia set status = 1, data2 = '$data' where id = $id";
		
		if (mysqli_query($conn, $update)) {
		
          echo "Update com sucesso!";
		} else {
			  echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}
		
		if($status == 2){
		$sql = "INSERT INTO sensor_energia (status) VALUES ($status)";
		if (mysqli_query($conn, $sql)) {
          echo "Valores salvo com sucesso!";
		
		} else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}
	
	if($status == 3){
		
		$consulta = "select * from sensor_energia where status = 2 and data2 is NULL";
		$resultado = mysqli_query($conn,$consulta) or die("Erro ao retornar dados");
		while ($registro = mysqli_fetch_array($resultado)){
			$id = $registro['id'];
		}
		$update = "update sensor_energia set status = 3, data2 = '$data' where id = $id";
		
		if (mysqli_query($conn, $update)) {
          echo "Update com sucesso!";
	 
		} else {
			  echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
		
		
	}
    
	

	
	if($status == 4){
		$sql = "INSERT INTO sensor_energia (status) VALUES ($status)";
		if (mysqli_query($conn, $sql)) {
          echo "Valores salvo com sucesso!";
	
		} else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}
	
	if($status == 5){
		
		$consulta = "select * from sensor_energia where status = 4 and data2 is NULL";
		$resultado = mysqli_query($conn,$consulta) or die("Erro ao retornar dados");
		while ($registro = mysqli_fetch_array($resultado)){
			$id = $registro['id'];
		}
		$update = "update sensor_energia set status = 5, data2 = '$data' where id = $id";
		
		if (mysqli_query($conn, $update)) {
          echo "Update com sucesso!";

		} else {
			  echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
		
		
	}
	
		if($status == 6){
		$sql = "INSERT INTO sensor_energia (status) VALUES ($status)";
		if (mysqli_query($conn, $sql)) {
          echo "Valores salvo com sucesso!";

		} else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
		}
	}
	
    mysqli_close($conn);


?>
