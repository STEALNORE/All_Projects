import os

ROOT = r"E:\SteamLibrary\steamapps\common\Game"

def replace_in_file(path):
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        text = f.read()

    # Меняем все варианты на правильный
    new_text = (
        text.replace("translate chinese", "translate Russian")
            .replace("translate russian", "translate Russian")
    )

    if new_text != text:  # если были изменения
        with open(path, "w", encoding="utf-8") as f:
            f.write(new_text)
        print(f"Обновлено: {path}")

def main():
    for root, dirs, files in os.walk(ROOT):
        for name in files:
            if name.lower().endswith(".rpy"):
                replace_in_file(os.path.join(root, name))

    print("Готово. Все вхождения заменены.")

if __name__ == "__main__":
    main()
