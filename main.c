#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    double cuocHanhLy;
};

int main() {
    int N;
    struct VeMayBay danhSachVe[MAX_VE];
    
    // 1. Nhập số lượng vé
    do {
        printf("Nhap so luong ve may bay (1 - 100): ");
        if (scanf("%d", &N) != 1) {
            while (getchar() != '\n'); // Xóa bộ đệm nếu nhập sai kiểu
            N = 0; 
        }
        if (N < 1 || N > 100) {
            printf("So luong khong hop le! Vui long nhap lai.\n");
        }
    } while (N < 1 || N > 100);
    
    while (getchar() != '\n'); // Làm sạch bộ đệm sau khi nhập N
    
    // 2 & 3. Nhập danh sách vé và tính cước phí
    for (int i = 0; i < N; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);
        
        printf("Ma ve PNR: ");
        fgets(danhSachVe[i].maVe, sizeof(danhSachVe[i].maVe), stdin);
        danhSachVe[i].maVe[strcspn(danhSachVe[i].maVe, "\n")] = '\0';
        
        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = '\0';
        
        printf("Hang ve (Business/Deluxe/Eco): ");
        fgets(danhSachVe[i].hangVe, sizeof(danhSachVe[i].hangVe), stdin);
        danhSachVe[i].hangVe[strcspn(danhSachVe[i].hangVe, "\n")] = '\0';
        
        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Khoi luong hanh ly khong the am. Vui long nhap lai!\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);
        
        while (getchar() != '\n'); // Làm sạch bộ đệm sau scanf chuẩn bị cho vòng lặp tiếp theo
        
        // Tính cước hành lý
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20) {
                danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000;
        }
    }
    
    // 4. Hiển thị danh sách vé, tổng cước và hành lý nặng nhất
    printf("\n================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n", "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("----------------------------------------------------------------------------------------------------\n");
    
    double tongCuoc = 0;
    int indexMax = 0;
    
    for (int i = 0; i < N; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n", 
            i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, 
            danhSachVe[i].hangVe, danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        
        tongCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[indexMax].canNangHanhLy) {
            indexMax = i;
        }
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    if (N > 0) {
        printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n", 
            danhSachVe[indexMax].maVe, danhSachVe[indexMax].tenHanhKhach, danhSachVe[indexMax].canNangHanhLy);
    }
    
    // 5. Cập nhật thông tin hành lý
    char pnrTimKiem[15];
    printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
    printf("Nhap ma ve PNR can cap nhat hanh ly: ");
    fgets(pnrTimKiem, sizeof(pnrTimKiem), stdin);
    pnrTimKiem[strcspn(pnrTimKiem, "\n")] = '\0';
    
    int foundIndex = -1;
    for (int i = 0; i < N; i++) {
        if (strcmp(danhSachVe[i].maVe, pnrTimKiem) == 0) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex != -1) {
        do {
            printf("Nhap can nang hanh ly ky gui moi (kg): ");
            scanf("%f", &danhSachVe[foundIndex].canNangHanhLy);
            if (danhSachVe[foundIndex].canNangHanhLy < 0) {
                printf("Khoi luong hanh ly khong the am. Vui long nhap lai!\n");
            }
        } while (danhSachVe[foundIndex].canNangHanhLy < 0);
        
        // Tính toán lại
        if (strcmp(danhSachVe[foundIndex].hangVe, "Business") == 0) {
            if (danhSachVe[foundIndex].canNangHanhLy <= 20) {
                danhSachVe[foundIndex].cuocHanhLy = 0;
            } else {
                danhSachVe[foundIndex].cuocHanhLy = (danhSachVe[foundIndex].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[foundIndex].cuocHanhLy = danhSachVe[foundIndex].canNangHanhLy * 50000;
        }
        
        printf("Tim thay ma ve %s. Da cap nhat cuoc hanh ly moi: %.0f VND.\n", 
            danhSachVe[foundIndex].maVe, danhSachVe[foundIndex].cuocHanhLy);
            
        // In lại bảng danh sách
        printf("\n================================ DANH SACH VE MAY BAY SAU CAP NHAT ================================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n", "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < N; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n", 
                i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, 
                danhSachVe[i].hangVe, danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    } else {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    }
    
    return 0;
}