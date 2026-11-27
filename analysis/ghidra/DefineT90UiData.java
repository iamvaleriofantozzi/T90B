import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.DWordDataType;

public class DefineT90UiData extends GhidraScript {
    @Override public void run() throws Exception {
        defineTable(0x08016050L, 44, "ui_message_pointers");
        defineTable(0x08016380L, 16, "ui_menu_pointers");
    }

    private void defineTable(long start, int count, String label) throws Exception {
        var memory = currentProgram.getMemory();
        for (int i = 0; i < count; i++) {
            var entry = toAddr(start + 4L * i);
            long target = Integer.toUnsignedLong(memory.getInt(entry));
            if (target < 0x0801c100L || target >= 0x0801c700L) {
                throw new IllegalStateException("Unexpected string pointer at " + entry);
            }
        }
        var first = toAddr(start);
        var last = first.add(4L * count - 1);
        clearListing(first, last);
        for (int i = 0; i < count; i++) {
            createData(first.add(4L * i), DWordDataType.dataType);
        }
        createLabel(first, label, true);
        println("Defined " + count + " entries for " + label);
    }
}
