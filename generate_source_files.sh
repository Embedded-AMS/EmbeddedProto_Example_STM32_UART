
# Generate the embedded source code.
mkdir -p ./nucleo-f446re/generated

cd EmbeddedProto
protoc --plugin=protoc-gen-eams=protoc-gen-eams -I../proto --eams_out=../nucleo-f446re/generated ../proto/uart_messages.proto
cd -

# Generate the desktop source code.
mkdir -p ./desktop/generated
protoc -I./proto --python_out=./desktop/generated ./proto/uart_messages.proto

