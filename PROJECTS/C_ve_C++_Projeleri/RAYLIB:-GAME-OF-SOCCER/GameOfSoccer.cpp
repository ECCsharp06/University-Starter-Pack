#include <iostream> // Ana kütüphanelerimiz
#include "raylib.h"
// Oyuncunun yatay hareketini sağlayan fonksiyon
void horizontalMove(Rectangle &rec, int screenWidth){
    const int margin = 15; // Görünmez duvar mesafesi

    if(IsKeyDown(KEY_RIGHT) && rec.x + rec.width + margin <= screenWidth){
        rec.x += 15;
    }
    if(IsKeyDown(KEY_LEFT) && rec.x - margin >= 0){
        rec.x -= 15;
    }
}
// Topa yerçekimi uygulayan fonksiyon
void applyGravityToBall(Rectangle &rec, int screenHeight, float &velocityY, float gravity){
    velocityY += gravity;
    rec.y += velocityY;

    if(rec.y + rec.height >= screenHeight){
        rec.y = screenHeight - rec.height;
        velocityY = 0;
    }
}
// Oyuncuya yerçekimi uygulayan fonksiyon
void applyGravity(Rectangle &rec, int screenHeight, float &velocityY, float gravity, bool &isJumping){
    velocityY += gravity;
    rec.y += velocityY;

    if(rec.y + rec.height >= screenHeight){
        rec.y = screenHeight - rec.height;
        velocityY = 0;
        isJumping = false; // Yere değdiğinde zıplama durumu sıfırlanır
    }
}
// Oyuncunun zıplamasını sağlayan fonksiyon
void jump(Rectangle &rec, float &velocityY, float jumpForce, bool &isJumping, Sound jumpSound){
    if(IsKeyPressed(KEY_UP) && !isJumping){
        velocityY = -jumpForce;
        isJumping = true; // Zıplama durumu aktif edilir
        PlaySound(jumpSound); // Zıplama sesi oynatılır
    }
}
// Çarpışma kontrolü yapan fonksiyon
bool checkCollision(Rectangle rec, Rectangle ball){
    return (rec.x < ball.x + ball.width &&
            rec.x + rec.width > ball.x &&
            rec.y < ball.y + ball.height &&
            rec.y + rec.height > ball.y);
}

void kickingBallUpwards(Rectangle rec, Rectangle &ball, float &ballVelocityY, float kickForce){
    if(checkCollision(rec, ball) && IsKeyDown(KEY_UP)){
        ballVelocityY = -kickForce * 1.25;
    }
}
// Sekiz bariyeri çizen ve her bariyerin görünme süresini kontrol eden fonksiyon
void eightBarrierDrawer(Rectangle barriers[], int &currentBarrier, float &timer, float interval){
    timer += GetFrameTime();
    if (timer >= interval) {
        timer = 0.0f;
        currentBarrier = (currentBarrier + 1) % 8;
    }

    for (int i = 0; i < 8; i++) {
        if (i == currentBarrier) {
            DrawRectangleRounded(barriers[i], 0.1, 0, RED);
        }
    }
}
// Topun belirli şartlar altında sıfırlanmasını sağlayabilmek için kullanılan fonksiyon
void resetBall(Rectangle &ball, float &ballVelocityX, float &ballVelocityY){
    ball.x = 600;
    ball.y = 400;
    ballVelocityX = 0;
    ballVelocityY = 0;
} 

/* Merhaba. Eğer burayı okuyorsanız eminim bu programın ne işe yaradığını merak ediyorsunuzdur.
 * Bu benim PAÜ'de okurken 1. sınıfın sömestır tatili boyunca yapmış olduğum bir yan projedir.
 * Bu program ufak bir oyun programıdır. Dosya isminden de anlamış olabilirsiniz belki, ufak bir futbol oyunudur.
 * Ortaya çıkan bariyerler oyuncu için bir engeldir ve oyunun asıl amacı bu engelleri aşıp topun kaleye girmesini sağlayarak
 * puan kazanmaktır. 
 * Bu program Raylib adlı oyun geliştirme kütüphanesinin yardımıyla çalışmaktadır. Bu kod içerisindeki birçok fonksiyon da
 * Raylib kütüphanesi tarafından oluşturulmuş entegre fonksiyonlardır. 
 * Bu ve bunun gibi oyunları tasarlamak için Raylib kütüphanesini veya başka oyun geliştirme kütüphanelerini kullanabilirsiniz.
 * Eğer Raylib'i bilgisayarınızda kurmak istiyorsanız faydalı olabilecek siteler:
 * https://www.raylib.com/ 
 * https://www.reddit.com/r/raylib/
 * DİKKAT! Raylib'in kurulumu çok karmaşık olabilir. Eğer yabancı dil olarak iyi bir miktarda ingilizce biliyorsanız aşağıdaki
 * YouTube videosu size yardımcı olabilir: 
 * https://www.youtube.com/watch?v=PaAcVk5jUd8 
 * Eğer Raylib hakkında daha kapsamlı bilgi istiyorsanız, Raylib'in ana geliştiricilerinden Raysan'ın GitHub hesabı aşağıdadır:
 * https://github.com/raysan5/raylib */

 // Ana Kod Bölümümüz
int main(){
    const int SCREEN_WIDTH = 1200; // Ekran genişliği ve yüksekliği
    const int SCREEN_HEIGHT = 800;
    const float GRAVITY = 0.5f; // Yerçekimi kuvveti
    const float JUMP_FORCE = 15.0f; // Oyuncunun zıplama kuvveti
    const float FRICTION = 0.95f; // Sürtünme kuvveti
    float velocityY = 0; // Oyuncunun başlangıçta dikey hızı
    float ballVelocityY = 0; // Topun başlangıçta dikey hızı
    float ballVelocityX = 0; // Topun başlangıçta yatay hızı
    bool isJumping = false; // Oyuncunun zıplama durumu
    int score = 0; // Oyuncunun skoru
    float ballTimer = 0.0f; // Topun kale direğinin önünde kalma süresi
    const float RESETING_LIMIT = 4.5f; // Topun kale direğinin önünde kalma süresi sınırı

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Of Soccer"); // Pencereyi başlat
    InitAudioDevice(); // Ses sistemini başlat
    SetTargetFPS(60); // FPS'yi ayarla

    Sound jumpSound = LoadSound("jump.wav"); // Zıplama sesi
    Sound goalSound = LoadSound("crowd-cheering-soccer.wav"); // Gol sesi

    // Program içerisinde kullanılan dokular. Dokular oyun içerisinde belirli görüntüleri sağlar. Dokular bu kod bloğuyla başlangıçta bir kez yüklenir.
    Texture2D playerRight = LoadTexture("playertextureright.png");
    Texture2D playerLeft = LoadTexture("playertextureleft.png");
    Texture2D playerStanding = LoadTexture("playertexturestanding.png");
    Texture2D playerJumping = LoadTexture("playertexturejumpingleft.png");
    Texture2D playerJumpingRight = LoadTexture("playertexturejumpingright.png");
    Texture2D player = playerStanding; 
    Texture2D balltexture = LoadTexture("soccerball.png");
    // Oyuncunun, topun, kale direklerinin ve bariyerlerin dikdörtgenlerini yani pozisyonlarını ve boyutlarını belirleyen kod bloğu
    Rectangle rec = { 7.5, 700, 75, 100 };
    Rectangle ball = { 600, 400, 39, 39 };
    Rectangle keepFence = {1000, 350, 10, 450};
    Rectangle keepFence2 = {1000, 350, 150, 10};
    Rectangle barriers[8] = {
        {775, 660, 35, 150},
        {775, 610, 35, 200},
        {775, 560, 35, 250},
        {775, 510, 35, 300},
        {775, 460, 35, 350},
        {775, 410, 35, 400},
        {775, 360, 35, 450},
        {775, 310, 35, 500}
    };

    int currentBarrier = 0; // Şu anki bariyerin indeksi
    float timer = 0.0f; // Bariyerlerin görünme süresini kontrol eden zamanlayıcı
    const float interval = 0.55f; // Her bariyerin görünme süresi (saniye)
    // Oyunun ana döngüsü
    while (!WindowShouldClose()){
        BeginDrawing(); // Çizim işlemlerini başlat
        ClearBackground(RAYWHITE); // Arka planı temizle

        // Oyuncunun yönüne göre dokuyu seç
        if(isJumping && IsKeyDown(KEY_RIGHT)){
            player = playerJumpingRight;
        }
        else if(isJumping && IsKeyDown(KEY_LEFT)){
            player = playerJumping;
        }
        else if(isJumping){
            player = playerJumpingRight;
        }
        else if(IsKeyDown(KEY_RIGHT)){
            player = playerRight;
        }
        else if(IsKeyDown(KEY_LEFT)){
            player = playerLeft;
        }
        else{
            player = playerStanding;
        }

        // Oyuncu dokusunu ölçekleyerek çiz
        Rectangle sourceRec = { 0.0f, 0.0f, (float)player.width, (float)player.height };
        Rectangle destRec;
        if (playerStanding.id == player.id) {
            destRec = { rec.x, rec.y-25, rec.width * 0.75f, rec.height*1.25f }; // Genişliği azalt
        }
        else if(playerJumping.id==player.id){
            destRec = { rec.x, rec.y-15, rec.width*1.1f, rec.height*1.10f };
        }
        else if(playerJumpingRight.id==player.id){
            destRec = { rec.x, rec.y-15, rec.width*1.1f, rec.height*1.10f };
        }
         else {
            destRec = { rec.x-25, rec.y-40, rec.width*1.65f, rec.height*1.60f };
        }
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(player, sourceRec, destRec, origin, 0.0f, WHITE);

        // Top dokusunu ölçekleyerek çiz
        Rectangle ballSourceRec = { 0.0f, 0.0f, (float)balltexture.width, (float)balltexture.height };
        Rectangle ballDestRec = { ball.x, ball.y, ball.width, ball.height };
        Vector2 ballOrigin = { 0.0f, 0.0f };

        // Kale direği ve file çizimleri için pozisyonlar
        Vector2 keepLineStartPos={1145,351};
        Vector2 keepLineEndPos={1250,700};
        Vector2 netLineStartPos={1025,360};
        Vector2 netLineEndPos={1025,800};
        Vector2 netLine2StartPos={1075,360};
        Vector2 netLine2EndPos={1075,800};
        Vector2 netLine3StartPos={1125,360};
        Vector2 netLine3EndPos={1125,800};
        Vector2 netLine4StartPos={1175,465};
        Vector2 netLine4EndPos={1175,800};
        Vector2 horizontalNetLineStartPos={1010,375};
        Vector2 horizontalNetLineEndPos={1150,375};
        Vector2 horizontalNetLine2StartPos={1010,465};
        Vector2 horizontalNetLine2EndPos={1175,465};
        Vector2 horizontalNetLine3StartPos={1010,555};
        Vector2 horizontalNetLine3EndPos={1200,555};
        Vector2 horizontalNetLine4StartPos={1010,645};
        Vector2 horizontalNetLine4EndPos={1200,645};
        Vector2 horizontalNetLine5StartPos={1010,735};
        Vector2 horizontalNetLine5EndPos={1200,735};
        // Top dokusunu çiz
        DrawTexturePro(balltexture, ballSourceRec, ballDestRec, ballOrigin, 0.0f, WHITE);
        // Oyunun arayüzü
        DrawText("Game Of Soccer", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Skor: %d",score), 10, 40, 20, DARKGRAY);

        // Saydam dikdörtgen çizimi için renk tanımlaması
        Color transparentMaroon = { 128, 0, 0, 0 };
        // Kale direği, top, oyuncu ve file çizimleri
        DrawRectangleRounded(rec, 0.1, 0, transparentMaroon);
        DrawRectangleRounded(ball, 1, 0, transparentMaroon);
        DrawRectangleRounded(keepFence, 0.1, 0, GRAY);
        DrawRectangleRounded(keepFence2, 0.1, 0, GRAY);
        DrawLineEx(keepLineStartPos, keepLineEndPos, 10, GRAY);
        DrawLineEx(netLineStartPos, netLineEndPos, 5, BLACK);
        DrawLineEx(netLine2StartPos, netLine2EndPos, 5, BLACK);
        DrawLineEx(netLine3StartPos, netLine3EndPos, 5, BLACK);
        DrawLineEx(netLine4StartPos, netLine4EndPos, 5, BLACK);
        DrawLineEx(horizontalNetLineStartPos, horizontalNetLineEndPos, 5, BLACK);
        DrawLineEx(horizontalNetLine2StartPos, horizontalNetLine2EndPos, 5, BLACK);
        DrawLineEx(horizontalNetLine3StartPos, horizontalNetLine3EndPos, 5, BLACK);
        DrawLineEx(horizontalNetLine4StartPos, horizontalNetLine4EndPos, 5, BLACK);
        DrawLineEx(horizontalNetLine5StartPos, horizontalNetLine5EndPos, 5, BLACK);
        DrawText("Oyuncu", rec.x + 10, rec.y - 35, 10, MAROON);

        horizontalMove(rec, SCREEN_WIDTH); // Oyuncunun yatay hareketini sağla
        applyGravity(rec, SCREEN_HEIGHT, velocityY, GRAVITY, isJumping); // Oyuncuya yerçekimi uygula
        jump(rec, velocityY, JUMP_FORCE, isJumping, jumpSound); // Oyuncunun zıplamasını sağla
        applyGravityToBall(ball, SCREEN_HEIGHT, ballVelocityY, GRAVITY); // Topa yerçekimi uygula
        kickingBallUpwards(rec, ball, ballVelocityY, JUMP_FORCE); // Oyuncunun topa vurmasını sağla

        // Oyuncu ve top çarpışma kontrolü
        if(checkCollision(rec, ball)){
            if(IsKeyDown(KEY_RIGHT)){
                ballVelocityX = 25; // Top sağa doğru hareket eder
            }
            else if(IsKeyDown(KEY_LEFT)){
                ballVelocityX = -25; // Top sola doğru hareket eder
            }
        }

        // Topun yatay hareketini güncelle ve sürtünme kuvveti uygula
        ball.x += ballVelocityX;
        ballVelocityX *= FRICTION;

        // Topun dikey hareketini güncelle ve sürtünme kuvveti uygula
        ball.y += ballVelocityY;
        ballVelocityY *= FRICTION;
        // Topun ekran sınırlarına çarpmasını kontrol et
        if(ball.x + ball.width >= SCREEN_WIDTH){
            ball.x -= ball.width * 1.25;
            ballVelocityX *= -1;
        }
        if(ball.x <= 0){
            ball.x += ball.width * 1.25;
            ballVelocityX *= -1;
        }
        // Topun üst kale direğine çarpmasının kontrolü ve kontrole göre topun yönünü değiştirme
        if(checkCollision(keepFence2, ball)){
            if(ball.x < keepFence2.x){
                ball.x = keepFence2.x - ball.width;
            }
            else if(ball.x + ball.width > keepFence2.x + keepFence2.width){
                ball.x = keepFence2.x + keepFence2.width;
            }
            if(ball.y < keepFence2.y){
                ball.y = keepFence2.y - ball.height;
            }
            else if(ball.y + ball.height > keepFence2.y + keepFence2.height){
                ball.y = keepFence2.y + keepFence2.height;
            }
            ballVelocityX *= -1;
            ballVelocityY *= -1;
        }
        // Topun bariyerlere çarpmasının kontrolü
        if(checkCollision(barriers[currentBarrier], ball)){
            // Topu bariyerin dışına it
            if (ball.x < barriers[currentBarrier].x) {
                ball.x = barriers[currentBarrier].x - ball.width;
            } else if (ball.x + ball.width > barriers[currentBarrier].x + barriers[currentBarrier].width) {
                ball.x = barriers[currentBarrier].x + barriers[currentBarrier].width;
            }
            if (ball.y < barriers[currentBarrier].y) {
                ball.y = barriers[currentBarrier].y - ball.height;
            } else if (ball.y + ball.height > barriers[currentBarrier].y + barriers[currentBarrier].height) {
                ball.y = barriers[currentBarrier].y + barriers[currentBarrier].height;
            }

            // Topun hareket yönünü değiştir
            ballVelocityX *= -1;
            ballVelocityY *= -1;
        }
        // Oyuncunun bariyerlere çarpmasının kontrolü
        if(checkCollision(barriers[currentBarrier], rec)){
            // Oyuncuyu bariyerin dışına itmek yerine hareketini durdur
            if (rec.x < barriers[currentBarrier].x) {
                rec.x = barriers[currentBarrier].x - rec.width;
            } else if (rec.x + rec.width > barriers[currentBarrier].x + barriers[currentBarrier].width) {
                rec.x = barriers[currentBarrier].x + barriers[currentBarrier].width;
            }
            if (rec.y < barriers[currentBarrier].y) {
                rec.y = barriers[currentBarrier].y - rec.height;
            } else if (rec.y + rec.height > barriers[currentBarrier].y + barriers[currentBarrier].height) {
                rec.y = barriers[currentBarrier].y + barriers[currentBarrier].height;
            }
        }
        // Gol atılmasının kontrolü
        static bool goalScored = false;
        // Top kaleye girdiyse skoru arttır ve gol sesi çal
        if(ball.x + ball.width > keepFence.x+keepFence.width+39 && !goalScored){
            score++;
            PlaySound(goalSound);
            goalScored = true;
        }
        
        if(ball.x + ball.width <= keepFence.x){
            goalScored = false;
        }
        // Gol atıldığında topu başlangıç pozisyonuna geri döndür ( Burada niye resetBall kullanmadığımı hatırlamıyorum :) )
        if(goalScored){
            ball.x=600;
            ball.y=400;
            ballVelocityX=0;
            ballVelocityY=0;
        }
        // Sekiz bariyeri çiz ve her bariyerin görünme süresini kontrol et.
        eightBarrierDrawer(barriers, currentBarrier, timer, interval);

        // Topun kale direğinin önünde kalma süresini kontrol et
        if(ball.x <= keepFence.x && 825 <= ball.x){
            ballTimer += GetFrameTime();
        } else {
            ballTimer = 0.0f;
        }
        // Topun kale direğinin önünde belirli bir süre kalması durumunda topu başlangıç pozisyonuna geri döndür
        if(ballTimer >= RESETING_LIMIT){
            resetBall(ball, ballVelocityX, ballVelocityY);
            ballTimer = 0.0f; // Timer'ı sıfırla
        }
        // Çizim işlemlerini bitir
        EndDrawing();
    }

    // Dokuları serbest bırak
    UnloadTexture(playerRight);
    UnloadTexture(playerLeft);
    UnloadTexture(playerStanding);
    UnloadTexture(playerJumping);
    UnloadTexture(playerJumpingRight);
    UnloadTexture(balltexture);
    // Ses dosyalarını serbest bırak
    UnloadSound(jumpSound);
    UnloadSound(goalSound);
    CloseAudioDevice(); // Ses sistemini kapat
    // Pencereyi kapat
    CloseWindow();
    return 0;
}
/* Eğer istiyorsanız eightBarrierDrawer gibi fonksiyonları değiştirebilirsiniz. 
 * Bu program benim gibi daha yeni başlayanlar için zor olabilir. O yüzden araştırma yapmayı ve gerekirse ChatGPT veya GitHub
 * Copilot gibi yapay zeka modellerini kullanmaktan çekinmeyin. :)*/
