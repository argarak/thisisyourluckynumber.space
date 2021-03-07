<?php

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = filter_var($_POST['username'], FILTER_SANITIZE_STRING);

    if (strlen($username) > 16 || strlen($username) < 1) {
        $_SESSION['error'] = "ERROR: please enter a valid username!";
    } else {
        $userfile = fopen("/var/www/html/user", "w");
        fwrite($userfile, $username . "\n");
        fclose($userfile);

        $_SESSION['success'] = "SUCCESS: please wait for your request to appear on stream!";
    }
}

?>

<html>
    <head>
        <title>this is your lucky number . space</title>
        <link href="main.css" rel="stylesheet"/>
    </head>

    <body>
        <script src="https://cdn.jsdelivr.net/npm/hls.js@latest"></script>

        <div id="allContainer">

            <?php if (isset($_SESSION['error'])): ?>
                <div class="error">
                    <?php
                    echo $_SESSION['error'];
                    unset($_SESSION['error']);
                    ?>
                </div>
            <?php endif; ?>

            <?php if (isset($_SESSION['success'])): ?>
                <div class="success">
                    <?php
                    echo $_SESSION['success'];
                    unset($_SESSION['success']);
                    ?>
                </div>
            <?php endif; ?>

            <h1>thisisyourluckynumber.space</h1>
            <h3>find your lucky number using state-of-the-art hardware and streaming tech!</h3>

            <div class="videoContainer">
                <div class="videoOverlay" onclick="overlay()">
                    click here to view the stream!
                </div>
                <video id="video" autoplay>
                    <!-- Fallback here -->
                </video>
            </div>

            <p class="description">
                by clicking the button below, your username will get transmitted to my laptop, which will then send the username onto the arduino mega, which will then display on the board and, most importantly, generate your lucky number!
            </p>

            <p class="description">
                <strong>your lucky number will appear next to the username you entered!</strong>
            </p>

            <form action="index.php" method="post">

                <label for="username">input your username (16 characters max):</label>
                <input name="username" type="text" value="" minlength="1" maxlength="16" pattern="[a-zA-Z1-9\-_\s]+" required/>

                <input type="submit" value="give me the lucky number!">

            </form>
        </div>

        <script>
         function overlay() {
             video.play();
             document.querySelector(".videoOverlay").style.display = "none";
         }

         var video = document.getElementById('video');
         var videoSrc = 'http://thisisyourluckynumber.space/hls/lucky.m3u8';
         if (Hls.isSupported()) {
             var hls = new Hls();
             hls.loadSource(videoSrc);
             hls.attachMedia(video);
         }
         // hls.js is not supported on platforms that do not have Media Source
         // Extensions (MSE) enabled.
         //
         // When the browser has built-in HLS support (check using `canPlayType`),
         // we can provide an HLS manifest (i.e. .m3u8 URL) directly to the video
         // element through the `src` property. This is using the built-in support
         // of the plain video element, without using hls.js.
         //
         // Note: it would be more normal to wait on the 'canplay' event below however
         // on Safari (where you are most likely to find built-in HLS support) the
         // video.src URL must be on the user-driven white-list before a 'canplay'
         // event will be emitted; the last video event that can be reliably
         // listened-for when the URL is not on the white-list is 'loadedmetadata'.
         else if (video.canPlayType('application/vnd.apple.mpegurl')) {
             video.src = videoSrc;
         }
        </script>

    </body>

</html>
