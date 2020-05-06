<?php
        include "conecta.php";

        $status = $_GET['status'];
	$data = date ('Y/m/d H:i:s');


         switch($status){
    case 1:
                $sql = "update sensor_status set status = $status, data = '$data'";
                if (mysqli_query($conn, $sql)) {
          echo "Update com sucesso!";
		  mysqli_close($conn);
                } else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
                }


          break;
    case 2 :

     $sql = "update sensor_status set status = $status, data = '$data'";
                if (mysqli_query($conn, $sql)) {
          echo "Update com sucesso!";
		  mysqli_close($conn);
                } else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
                }
        break;
    default:
          $sql = "insert into sensor_status (status) values (0)";
                if (mysqli_query($conn, $sql)) {
          echo "Insert com sucesso!";
		  mysqli_close($conn);
                } else {
          echo "Error: " . $sql . "<br>" . mysqli_error($conn);
                }

         break;
}

?>

