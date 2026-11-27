import java.nio.file.Files;
import java.nio.file.Path;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.CodeUnit;

public class AnnotateT90 extends GhidraScript {
    @Override public void run() throws Exception {
        int annotated = 0;
        var rows = Files.readAllLines(Path.of(getScriptArgs()[0]));
        for (String row : rows.subList(1, rows.size())) {
            String[] fields = row.split("\t");
            String[] evidence = fields[3].split("; literal load a ", 2);
            String note = "NSING N32L403: literal " + fields[0] + " (" + fields[2] +
                "." + fields[1] + "); may represent a peripheral base.";
            for (String site : evidence[1].split(", ")) {
                var instruction = getInstructionAt(toAddr(site));
                if (instruction == null) {
                    throw new IllegalStateException("Missing instruction at " + site);
                }
                instruction.setComment(CodeUnit.EOL_COMMENT, note);
                annotated++;
            }
        }
        println("Annotated " + annotated + " literal loads.");
    }
}
