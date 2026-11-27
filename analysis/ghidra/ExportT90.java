import java.nio.file.Files;
import java.nio.file.Path;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.script.GhidraScript;

public class ExportT90 extends GhidraScript {
    @Override public void run() throws Exception {
        Path output = Path.of(getScriptArgs()[0]);
        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram))
            throw new IllegalStateException(decompiler.getLastMessage());
        int total = 0;
        int completed = 0;
        try (var c = Files.newBufferedWriter(output.resolve("t90-pseudocode.c"));
             var index = Files.newBufferedWriter(output.resolve("functions.tsv"));
             var asm = Files.newBufferedWriter(output.resolve("t90-disassembly.txt"))) {
            c.write("/* Ghidra pseudocode, generated from t90.atk. Not buildable C. */\n");
            index.write("address\tfunction\tdecompiled\n");
            var functions = currentProgram.getFunctionManager().getFunctions(true);
            while (functions.hasNext() && !monitor.isCancelled()) {
                var function = functions.next();
                var result = decompiler.decompileFunction(function, 30, monitor);
                boolean ok = result.decompileCompleted() && result.getDecompiledFunction() != null;
                total++;
                index.write(function.getEntryPoint() + "\t" + function.getName() + "\t" + ok + "\n");
                c.write("\n/* " + function.getEntryPoint() + " " + function.getName() + " */\n");
                if (ok) {
                    c.write(result.getDecompiledFunction().getC());
                    completed++;
                }
            }
            var instructions = currentProgram.getListing().getInstructions(true);
            while (instructions.hasNext()) {
                var instruction = instructions.next();
                asm.write(instruction.getAddress() + "  " + instruction + "\n");
            }
        } finally {
            decompiler.dispose();
        }
        println("Decompiled " + completed + "/" + total + " identified functions");
    }
}
