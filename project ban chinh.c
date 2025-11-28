#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char productId[20];
    char name[50];
    int qty;
    char unit[20];
    int status;
} Material;

Material materials[100];
int materialCount = 0;

void clearInput() {
    while (getchar() != '\n');
}

int is_empty(const char *str) {
    if (!str) return 1;
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

int findMaterialById(const char *id) {
    for (int i = 0; i < materialCount; i++) {
        if (strcmp(materials[i].productId, id) == 0)
            return i;
    }
    return -1;
}

void inputString(const char *message, char *buffer, int size) {
    while (1) {
        printf("%s", message);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (is_empty(buffer))
            printf("Khong duoc de trong. Nhap lai.\n");
        else
            break;
    }
}

int getNumber(char suggest[], int min, int max) {
    char string[50];
    int number;
    while (1) {
        printf("%s (tu %d den %d): ", suggest, min, max);
        fgets(string, sizeof(string), stdin);
        string[strcspn(string, "\n")] = '\0';
        if (is_empty(string)) {
            printf("Khong duoc de trong!\n");
            continue;
        }
        int ok = 1;
        for (int i = 0; i < strlen(string); i++) {
            if (!isdigit(string[i])) {
                ok = 0;
                break;
            }
        }
        if (!ok) {
            printf("Vui long nhap so nguyen!\n");
            continue;
        }
        number = atoi(string);
        if (number < min || number > max) {
            printf("So phai trong khoang (%d - %d)!\n", min, max);
            continue;
        }
        return number;
    }
}

int getPositiveNumber(char suggest[]) {
    char string[50];
    int number;
    while (1) {
        printf("%s: ", suggest);
        fgets(string, sizeof(string), stdin);
        string[strcspn(string, "\n")] = '\0';
        if (is_empty(string)) {
            printf("Khong duoc de trong!\n");
            continue;
        }
        int ok = 1;
        for (int i = 0; i < strlen(string); i++) {
            if (!isdigit(string[i])) {
                ok = 0;
                break;
            }
        }
        if (!ok) {
            printf("Vui long nhap so nguyen!\n");
            continue;
        }
        number = atoi(string);
        if (number < 0) {
            printf("So luong phai >= 0!\n");
            continue;
        }
        return number;
    }
}

void initMerchandise() {
    Material sample[20] = {
        {"P001", "Ga", 50, "kg", 1},
        {"P002", "Bo", 30, "kg", 1},
        {"P003", "Heo", 20, "kg", 1},
        {"P004", "Ca", 40, "kg", 1},
        {"P005", "Tom", 60, "kg", 1},
        {"P006", "Sua", 100, "lit", 1},
        {"P007", "Banh mi", 200, "cai", 1},
        {"P008", "Banh ngot", 150, "cai", 1},
        {"P009", "Rau cai", 70, "kg", 1},
        {"P010", "Ca rot", 80, "kg", 1},
        {"P011", "Dua leo", 60, "kg", 1},
        {"P012", "Tom", 55, "kg", 1},
        {"P013", "Gao", 500, "kg", 1},
        {"P014", "Duong", 400, "kg", 1},
        {"P015", "Muoi", 300, "kg", 1},
        {"P016", "Tra", 250, "goi", 1},
        {"P017", "Cafe", 150, "goi", 1},
        {"P018", "Nuoc ngot", 200, "chai", 1},
        {"P019", "Bia", 180, "chai", 1},
        {"P020", "Ruou vang", 120, "chai", 1}
    };
    for (int i = 0; i < 20; i++) {
        materials[materialCount++] = sample[i];
    }
}

void createNewMaterial() {
    Material m;
    m.status = 1;
    while (1) {
        inputString("Nhap ma hang hoa: ", m.productId, sizeof(m.productId));
        if (is_empty(m.productId)) continue;
        if (findMaterialById(m.productId) != -1) {
            printf("Ma hang hoa da ton tai. Nhap lai.\n");
            continue;
        }
        break;
    }
    while (1) {
        inputString("Nhap ten hang hoa: ", m.name, sizeof(m.name));
        if (is_empty(m.name)) continue;
        break;
    }
    m.qty = getPositiveNumber("Nhap so luong ton kho");
    while (1) {
        inputString("Nhap don vi hang hoa: ", m.unit, sizeof(m.unit));
        if (is_empty(m.unit)) continue;
        break;
    }
    materials[materialCount++] = m;
    printf("Them moi hang hoa thanh cong.\n");
}

void updateExistedProduct() {
    char id[20];
    inputString("Nhap ma hang hoa can cap nhat: ", id, sizeof(id));
    int index = findMaterialById(id);
    if (index == -1) {
        printf("Vat tu %s khong ton tai.\n", id);
        return;
    }
    Material *m = &materials[index];
    while (1) {
        inputString("Nhap ten hang hoa moi: ", m->name, sizeof(m->name));
        if (is_empty(m->name)) continue;
        break;
    }
    m->qty = getPositiveNumber("Nhap so luong moi");
    while (1) {
        inputString("Nhap don vi moi: ", m->unit, sizeof(m->unit));
        if (is_empty(m->unit)) continue;
        break;
    }
    printf("Cap nhat hang hoa %s thanh cong.\n", id);
}

void managementStatus() {
    char temp_id[20];
    int found = 0;
    int action;

    do {
        printf("Nhap ma san pham can thao tac: ");
        fgets(temp_id, sizeof(temp_id), stdin);
        temp_id[strcspn(temp_id, "\n")] = 0;
        if (is_empty(temp_id))
            printf("Khong duoc de trong!\n");
    } while (is_empty(temp_id));

    for (int i = 0; i < materialCount; i++) {
        if (strcmp(materials[i].productId, temp_id) == 0) {
            found = 1;

            printf("1. Khoa san pham\n");
            printf("2. Mo khoa san pham\n");

            char input[10];
            while (1) {
                printf("Lua chon: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;

                if (is_empty(input)) {
                    printf("Khong duoc de trong!\n");
                    continue;
                }

                if (strlen(input) != 1 || (input[0] != '1' && input[0] != '2')) {
                    printf("Chi duoc nhap 1 hoac 2!\n");
                    continue;
                }

                action = input[0] - '0';
                break;
            }

            if (action == 1) {
                if (materials[i].status == 0)
                    printf("San pham da bi khoa.\n");
                else {
                    materials[i].status = 0;
                    printf("Da khoa san pham %s.\n", materials[i].name);
                }
            } else if (action == 2) {
                if (materials[i].status == 1)
                    printf("San pham da dang mo.\n");
                else {
                    materials[i].status = 1;
                    printf("Da mo khoa san pham %s.\n", materials[i].name);
                }
            }

            break;
        }
    }

    if (!found)
        printf("Khong tim thay san pham!\n");
}

void findMaterial() {
    char id[20];
    inputString("Nhap ma hang hoa can tim: ", id, sizeof(id));
    int index = findMaterialById(id);
    if (index == -1) {
        printf("Khong tim thay.\n");
        return;
    }
    Material m = materials[index];
    printf("\n=== KET QUA ===\n");
    printf("ID: %s | Ten: %s | SL: %d | Don vi: %s | Status: %d\n",
           m.productId, m.name, m.qty, m.unit, m.status);
}

void findMaterialByName() {
    char name[50];
    inputString("Nhap ten hang hoa can tim: ", name, sizeof(name));

    char lowerInput[50];
    for (int i = 0; i < strlen(name); i++)
        lowerInput[i] = tolower(name[i]);
    lowerInput[strlen(name)] = '\0';

    int found = 0;

    printf("\n=== KET QUA TIM KIEM THEO TEN ===\n");
    printf("%-10s %-20s %-10s %-10s %-6s\n", "Ma", "Ten", "SL", "Don vi", "Status");

    for (int i = 0; i < materialCount; i++) {
        char lowerName[50];
        for (int j = 0; j < strlen(materials[i].name); j++)
            lowerName[j] = tolower(materials[i].name[j]);
        lowerName[strlen(materials[i].name)] = '\0';

        if (strstr(lowerName, lowerInput) != NULL) {
            found = 1;
            printf("%-10s %-20s %-10d %-10s %-6d\n",
                   materials[i].productId,
                   materials[i].name,
                   materials[i].qty,
                   materials[i].unit,
                   materials[i].status);
        }
    }

    if (!found)
        printf("Khong tim thay hang hoa nao phu hop.\n");
}

void listMaterials(int itemPerPage) {
    if (materialCount == 0) {
        printf("Danh sach rong.\n");
        return;
    }

    int totalPages = materialCount / itemPerPage + (materialCount % itemPerPage != 0);
    int page = 1;
    char input[10];

    while (1) {
        int start = (page - 1) * itemPerPage;
        int end = start + itemPerPage;
        if (end > materialCount) end = materialCount;

        printf("\n=== Trang %d / %d ===\n", page, totalPages);
        printf("%-10s %-20s %-10s %-10s %-6s\n", "Ma", "Ten", "SL", "Don vi", "Status");

        for (int i = start; i < end; i++) {
            printf("%-10s %-20s %-10d %-10s %-6d\n",
                   materials[i].productId,
                   materials[i].name,
                   materials[i].qty,
                   materials[i].unit,
                   materials[i].status);
        }

        while (1) {
            printf("\nA: Trang sau | S: Trang truoc | D: Thoat\n");
            printf("Lua chon: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (is_empty(input)) {
                printf("Khong duoc de trong! Vui long nhap lai.\n");
                continue;
            }

            if (strlen(input) != 1) {
                printf("Chi duoc nhap mot ky tu! Vui long nhap lai.\n");
                continue;
            }

            char temp = input[0];

            if (temp == 'A' || temp == 'a') {
                if (page < totalPages) page++;
                else printf("Day la trang cuoi.\n");
                break;
            } else if (temp == 'S' || temp == 's') {
                if (page > 1) page--;
                else printf("Day la trang dau.\n");
                break;
            } else if (temp == 'D' || temp == 'd') {
                return;
            } else {
                printf("Lua chon khong hop le! Vui long nhap lai.\n");
            }
        }
    }
}

void sortMaterials() {
    if (materialCount == 0) {
        printf("Danh sach hang hoa rong.\n");
        return;
    }
    printf("Chon kieu sap xep:\n");
    printf("1. Ten A-Z\n");
    printf("2. Ten Z-A\n");
    printf("3. So luong tang dan\n");
    printf("4. So luong giam dan\n");
    int choice = getNumber("Nhap lua chon", 1, 4);

    for (int i = 0; i < materialCount - 1; i++) {
        for (int j = i + 1; j < materialCount; j++) {
            int swapFlag = 0;
            if (choice == 1 && strcmp(materials[i].name, materials[j].name) > 0) swapFlag = 1;
            if (choice == 2 && strcmp(materials[i].name, materials[j].name) < 0) swapFlag = 1;
            if (choice == 3 && materials[i].qty > materials[j].qty) swapFlag = 1;
            if (choice == 4 && materials[i].qty < materials[j].qty) swapFlag = 1;

            if (swapFlag) {
                Material temp = materials[i];
                materials[i] = materials[j];
                materials[j] = temp;
            }
        }
    }

    printf("Sap xep thanh cong. Hien thi danh sach:\n");
    listMaterials(5);
}

int main() {
    int choice;
    initMerchandise();

    do {
        printf("||==========QUAN LY CUA HANG==========||\n");
        printf("|| 1. Them mat hang moi               ||\n");
        printf("|| 2. Cap nhat thong tin              ||\n");
        printf("|| 3. Quan ly trang thai              ||\n");
        printf("|| 4. Tra cuu                         ||\n");
        printf("|| 5. Danh sach (phan theo trang)     ||\n");
        printf("|| 6. Sap xep danh sach hang hoa      ||\n");
        printf("|| 7. Giao dich                       ||\n");
        printf("|| 8. Lich su giao dich               ||\n");
        printf("|| 0. Thoat                           ||\n");
        printf("||====================================||\n");

        choice = getNumber("Nhap lua chon", 0, 8);

        switch (choice) {
            case 1:
                createNewMaterial();
                break;

            case 2:
                updateExistedProduct();
                break;

            case 3:
                managementStatus();
                break;

            case 4: {
                printf("\n1. Tim theo ma hang\n");
                printf("2. Tim theo ten hang\n");
                int opt = getNumber("Chon kieu tim kiem", 1, 2);

                if (opt == 1) findMaterial();
                else findMaterialByName();
                break;
            }

            case 5:
                listMaterials(5);
                break;

            case 6:
                sortMaterials();
                break;

            case 7:
                break;

            case 8:
                break;

            case 0:
                printf("Thoat chuong trinh\n");
                break;

            default:
                printf("Lua chon khong hop le\n");
        }

    } while (choice != 0);

    return 0;
}

