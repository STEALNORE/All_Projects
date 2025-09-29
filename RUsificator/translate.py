# translate_in_place.py
import os
import re
from deep_translator import GoogleTranslator

ROOT = r"E:\SteamLibrary\steamapps\common\Game"

translator = GoogleTranslator(source="en", target="ru")

# Регэкспы
re_comment_en = re.compile(r'^\s*#.*?"([^"]+)"')          # # ... "English"
re_old        = re.compile(r'^\s*old\s+"([^"]+)"\s*$')     # old "English"
re_new        = re.compile(r'^\s*new\s+"([^"]*)"(.*)$')    # new "..."
re_quoted     = re.compile(r'"([^"]*)"')                   # первое "..."

def translate_text(txt: str) -> str:
    txt = txt.strip()
    if not txt:
        return txt
    try:
        return translator.translate(txt)
    except Exception:
        # если сервис отвалился — оставляем оригинал
        return txt

def process_file(path: str) -> None:
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    out_lines = []
    pending_from_comment = None  # перевод, полученный из верхней # "English"
    pending_from_old = None      # перевод, полученный из old "English"

    total = len(lines)
    for i, line in enumerate(lines, start=1):
        # 1) Сначала пытаемся найти комментарий с английским текстом
        m_comment = re_comment_en.match(line)
        if m_comment:
            en = m_comment.group(1)
            pending_from_comment = translate_text(en)
            out_lines.append(line)  # сам комментарий не меняем
        else:
            # 2) Блоки old/new
            m_old = re_old.match(line)
            if m_old:
                en = m_old.group(1)
                pending_from_old = translate_text(en)
                out_lines.append(line)  # old-строку не меняем
            else:
                m_new = re_new.match(line)
                if m_new and pending_from_old is not None:
                    # заменяем содержимое new "..."
                    tail = m_new.group(2)  # возможные суффиксы (комменты и т.п.)
                    new_line = f'    new "{pending_from_old}"{tail}\n'
                    out_lines.append(new_line)
                    pending_from_old = None
                else:
                    # 3) Если есть «ожидание» перевода из комментария — применяем к следующей реплике
                    if pending_from_comment is not None:
                        mq = re_quoted.search(line)
                        if mq:
                            start, end = mq.span(1)
                            new_line = line[:start] + pending_from_comment + line[end:]
                            out_lines.append(new_line)
                            pending_from_comment = None
                        else:
                            out_lines.append(line)
                    else:
                        out_lines.append(line)

        if i % 10 == 0 or i == total:
            print(f"{os.path.basename(path)}: {i}/{total}")

    # Сохраняем поверх
    with open(path, "w", encoding="utf-8") as f:
        f.writelines(out_lines)

def main():
    targets = []
    for root, dirs, files in os.walk(ROOT):
        for name in files:
            if name.lower().endswith(".rpy") and not name.lower().endswith(".rpyc"):
                targets.append(os.path.join(root, name))

    print(f"Найдено файлов: {len(targets)}")
    for idx, p in enumerate(targets, start=1):
        print(f"[{idx}/{len(targets)}] {p}")
        process_file(p)
    print("Готово.")

if __name__ == "__main__":
    main()
